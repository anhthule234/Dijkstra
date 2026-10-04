#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void dijkstra(int start, int n, vector<vector<pair<int, int>>>& adj) {
    // Kiểm tra đỉnh xuất phát hợp lệ
    if (start < 0 || start >= n) {
        cout << "Lỗi: Đỉnh xuất phát không hợp lệ!\n";
        return;
    }

    // priority_queue lưu {khoảng cách, đỉnh}, sắp xếp theo thứ tự tăng dần khoảng cách
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n, INT_MAX);

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Nếu tìm được khoảng cách ngắn hơn trước đó thì bỏ qua
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // 1. Cảnh báo nếu phát hiện trọng số âm
            if (weight < 0) {
                cout << "Cảnh báo: Cạnh (" << u << " -> " << v << ") có trọng số âm (" << weight
                     << "). Dijkstra có thể cho kết quả sai!\n";
            }

            // 2. Kiểm tra tránh tràn số (Overflow) trước khi cộng
            // Nếu dist[u] + weight vượt quá INT_MAX thì bỏ qua
            if (dist[u] != INT_MAX && weight > 0 && dist[u] > INT_MAX - weight) {
                continue;
            }

            // 3. Cập nhật khoảng cách ngắn hơn
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // 4. In kết quả, xử lý hiển thị cho đồ thị không liên thông
    cout << "\nKhoảng cách ngắn nhất từ đỉnh " << start << ":\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) {
            cout << "Node " << i << " : Không thể đến (INF)\n";
        } else {
            cout << "Node " << i << " : " << dist[i] << "\n";
        }
    }
}

int main() {
    int n = 5; // Số lượng đỉnh từ 0 đến 4
    vector<vector<pair<int, int>>> adj(n);

    // Thêm các cạnh (u, v, weight)
    // Đồ thị có một đỉnh độc lập (đỉnh 4) để test đồ thị không liên thông
    adj[0].push_back({1, 4});
    adj[0].push_back({2, 1});
    adj[2].push_back({1, 2});
    adj[1].push_back({3, 5});
    adj[2].push_back({3, 8});

    // Chạy thử thuật toán từ đỉnh xuất phát 0
    dijkstra(0, n, adj);

    // Chạy thử kiểm tra lỗi đỉnh xuất phát không hợp lệ
    cout << "\n--- Kiểm tra đỉnh không hợp lệ ---\n";
    dijkstra(5, n, adj);

    return 0;
}
