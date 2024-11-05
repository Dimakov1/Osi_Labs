#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point {
    double x, y;
    int cluster = -1;
};

double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) * 1.0 + (a.y - b.y) * (a.y - b.y) * 1.0);
}

void kMeansClustering(vector<Point> &points, int k) {
    vector<Point> centroids(k);
    srand(time(0));

    for (int i = 0; i < k; ++i) {
        centroids[i] = points[rand() % points.size()];
    }

    bool changed;
    int iterations = 0;
    const int max_iterations = 100;

    do {
        changed = false;

        for (auto &point : points) {
            int bestCluster = 0;
            double minDistance = distance(point, centroids[0]);

            for (int i = 1; i < k; ++i) {
                double dist = distance(point, centroids[i]);
                if (dist < minDistance) {
                    minDistance = dist;
                    bestCluster = i;
                }
            }

            if (point.cluster != bestCluster) {
                point.cluster = bestCluster;
                changed = true;
            }
        }

        vector<int> count(k, 0);
        vector<double> sumX(k, 0.0), sumY(k, 0.0);

        for (const auto &point : points) {
            sumX[point.cluster] += point.x;
            sumY[point.cluster] += point.y;
            count[point.cluster]++;
        }

        for (int i = 0; i < k; ++i) {
            if (count[i] > 0) {
                centroids[i].x = sumX[i] / count[i];
                centroids[i].y = sumY[i] / count[i];
            }
        }

        iterations++;

    } while (changed && iterations < max_iterations);

    for (int i = 0; i < k; ++i) {
        cout << "Кластер " << i + 1 << " центр: (" << centroids[i].x << ", " << centroids[i].y << ")\n";
    }

    for (size_t i = 0; i < points.size(); ++i) {
        cout << "Точка " << i + 1 << " (" << points[i].x << ", " << points[i].y << ") принадлежит кластеру " << points[i].cluster + 1 << "\n";
    }
}

int main() {
    int n, k;

    cout << "Введите количество точек: ";
    cin >> n;

    vector<Point> points(n);

    cout << "Введите координаты точек (x y):\n";
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    cout << "Введите количество кластеров: ";
    cin >> k;

    kMeansClustering(points, k);

    return 0;
}


 