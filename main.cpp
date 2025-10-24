#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Movie {
    string name;
    string genre;
    float rating;
};

class MovieSystem {
    unordered_map<string, vector<Movie>> genreMap;
public:
    void addMovie(string name, string genre, float rating) {
        Movie m = {name, genre, rating};
        genreMap[genre].push_back(m);
    }

    void displayAll() {
        for (auto& g : genreMap) {
            cout << "\nGenre: " << g.first << endl;
            for (auto& m : g.second)
                cout << "  " << m.name << " (" << m.rating << ")\n";
        }
    }

    void recommendTop(string genre, int n) {
        if (genreMap.find(genre) == genreMap.end()) {
            cout << "No movies found for this genre.\n";
            return;
        }
        auto cmp = [](Movie a, Movie b) { return a.rating < b.rating; };
        priority_queue<Movie, vector<Movie>, decltype(cmp)> pq(cmp);
        for (auto& m : genreMap[genre]) pq.push(m);
        cout << "\nTop " << n << " movies in " << genre << ":\n";
        for (int i = 0; i < n && !pq.empty(); i++) {
            Movie top = pq.top();
            pq.pop();
            cout << i + 1 << ". " << top.name << " (" << top.rating << ")\n";
        }
    }

    void searchMovie(string name) {
        for (auto& g : genreMap)
            for (auto& m : g.second)
                if (m.name == name) {
                    cout << "Found: " << m.name << " | Genre: " << m.genre << " | Rating: " << m.rating << endl;
                    return;
                }
        cout << "Movie not found.\n";
    }
};

int main() {
    MovieSystem ms;
    int choice;
    do {
        cout << "\n===== Movie Recommendation System =====\n";
        cout << "1. Add Movie\n";
        cout << "2. Display All Movies\n";
        cout << "3. Search Movie by Name\n";
        cout << "4. Recommend Top Movies by Genre\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            string name, genre;
            float rating;
            cout << "Enter Movie Name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter Genre: ";
            getline(cin, genre);
            cout << "Enter Rating: ";
            cin >> rating;
            ms.addMovie(name, genre, rating);
        } 
        else if (choice == 2) ms.displayAll();
        else if (choice == 3) {
            string name;
            cout << "Enter Movie Name: ";
            cin >> ws;
            getline(cin, name);
            ms.searchMovie(name);
        }
        else if (choice == 4) {
            string genre;
            int n;
            cout << "Enter Genre: ";
            cin >> ws;
            getline(cin, genre);
            cout << "How many top movies?: ";
            cin >> n;
            ms.recommendTop(genre, n);
        }
        else if (choice == 5) cout << "Exiting...\n";
        else cout << "Invalid choice.\n";
    } while (choice != 5);
    return 0;
}
