#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>

struct Point {
    double x, y;
    int cluster = -1;
};

struct ThreadData {
    std::vector<Point>* points;
    std::vector<Point>* centroids;
    int start;
    int end;
    int k;
};

pthread_mutex_t mutex;

double distance(const Point &a, const Point &b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void* assignClusters(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start; i < data->end; ++i) {
        double minDist = distance((*data->points)[i], (*data->centroids)[0]);
        int bestCluster = 0;
        for (int j = 1; j < data->k; ++j) {
            double dist = distance((*data->points)[i], (*data->centroids)[j]);
            if (dist < minDist) {
                minDist = dist;
                bestCluster = j;
            }
        }
        (*data->points)[i].cluster = bestCluster;
    }
    return nullptr;
}

void kMeansClustering(std::vector<Point>& points, int k, int maxThreads) {
    std::vector<Point> centroids(k);
    std::srand(std::time(0));

    for (int i = 0; i < k; ++i) {
        centroids[i] = points[std::rand() % points.size()];
    }

    bool changed;
    int iterations = 0;
    const int maxIterations = 100;

    do {
        changed = false;

        int pointsPerThread = points.size() / maxThreads;
        pthread_t threads[maxThreads];
        ThreadData threadData[maxThreads];

        for (int i = 0; i < maxThreads; ++i) {
            int start = i * pointsPerThread;
            int end;
            if (i == maxThreads - 1) {
                end = points.size();
            } else {
                end = (i + 1) * pointsPerThread;
            }
            
            threadData[i] = { &points, &centroids, start, end, k };

            if (pthread_create(&threads[i], nullptr, assignClusters, &threadData[i]) != 0) {
                std::cerr << "Ошибка при создании потока\n";
                exit(1);
            }
        }

        for (int i = 0; i < maxThreads; ++i) {
            pthread_join(threads[i], nullptr);
        }

        std::vector<int> count(k, 0);
        std::vector<double> sumX(k, 0.0), sumY(k, 0.0);

        for (const auto &point : points) {
            sumX[point.cluster] += point.x;
            sumY[point.cluster] += point.y;
            count[point.cluster]++;
        }

        for (int i = 0; i < k; ++i) {
            if (count[i] > 0) {
                Point newCentroid = { sumX[i] / count[i], sumY[i] / count[i] };
                if (centroids[i].x != newCentroid.x || centroids[i].y != newCentroid.y) {
                    changed = true;
                }
                centroids[i] = newCentroid;
            }
        }

        iterations++;

    } while (changed && iterations < maxIterations);

    for (int i = 0; i < k; ++i) {
        std::cout << "Кластер " << i + 1 << " центр: (" << centroids[i].x << ", " << centroids[i].y << ")\n";
    }

    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << "Точка " << i + 1 << " (" << points[i].x << ", " << points[i].y << ") принадлежит кластеру " << points[i].cluster + 1 << "\n";
    }
}

int main() {
    int maxThreads;

    std::cout << "Введите максимальное количество потоков:\n";
    std::cin >> maxThreads;

    int n, k;
    std::cout << "Введите количество точек:\n";
    std::cin >> n;

    std::vector<Point> points(n);
    std::cout << "Введите координаты точек (x y):\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    std::cout << "Введите количество кластеров:\n";
    std::cin >> k;

    kMeansClustering(points, k, maxThreads);

    std::cout << "Используемое количество потоков: " << maxThreads << std::endl;

    return 0;
}
