//TSP: version: 18, Final 

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <csignal>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::reverse;

typedef struct {
    int id;
    int x_pos;
    int y_pos;
    int visit;
} city;

int best_distance = INT_MAX;


void input(string input_file, vector <city> &city_input);


void output(string output_file, int tour_distance, vector<int> city_order);


int distance(city city1, city city2);

void nearest(int start, int &tour_distance, string output_file, vector <city> &city_data, vector <int> &city_order);

void two_opt(int &tour_distance, string output_file, vector <city> &city_data, vector <int> &city_order);

void signal_handler(int signum);

int main(int argc, char* argv[]) {
    string input_file;
    string output_file;
    int tour_distance;

    vector <city> city_data;
    vector <int> city_order;
    vector <int> best_order;
    vector <int> visits;

    // register signal SIGINT and signal handler
    signal(SIGTERM, signal_handler);

    if (argc == 2){
        input_file = string(argv[1]);
        output_file = string(argv[1]) + ".tour";
    }
    else{
        cout << "Should give input file." << endl;
        exit (EXIT_FAILURE);
    }

    cout << "Reading " << input_file << "." << endl;

    input(input_file, city_data);

    cout << endl << "Cities: " << (int)city_data.size() << endl;

    //calculates a TSP tour using the nearest neighbor algorithm and 2-opt optimization
    clock_t start,end, start1,end1;
    double timer;
    double timer1 = 0;
    int cityid = 0;
    start = clock();
    while(timer1 < 300 && cityid < (int)city_data.size())
  	{
    for (int i = 0; i < (int)city_data.size(); i++){
        tour_distance = 0;
        city_order.clear();
        for (int j = 0; j < (int)city_data.size(); j++){
            city_data[j].visit = 0;
        }
        start1 = clock();
        nearest(i, tour_distance, output_file, city_data, city_order);

        two_opt(tour_distance, output_file, city_data, city_order);
        end1 = clock();
        timer = double(end1 - start1) / (double)CLOCKS_PER_SEC;
        timer1 = timer1 + timer;
        cityid++;
    	if(timer1 > 300)
    	{
    		cout << endl <<"Timer Expired 5 Minutes." <<endl;
    		break;
    	}
    }

}
    cout << endl << "The best tour found is " << best_distance << "." << endl << endl;
    end = clock();
    cout << "Run Time:" <<double( end - start) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    return 0;
}

void signal_handler(int signum){
    cout << "Interrupt signal (" << signum << ") received." << endl;
    cout << endl << "The best tour found is " << best_distance << "." << endl << endl;
    exit(signum);
}

void input(string input_file, vector <city> &city_data){
    ifstream input(input_file.c_str());
    string line;
    city temp;

    while (getline(input, line)){
        stringstream ss(line);
        if(ss >> temp.id >> temp.x_pos >> temp.y_pos){
            temp.visit = 0;
            city_data.push_back(temp);
        }
    }
    input.close();
}

void output(string output_file, int tour_distance, vector<int> city_order){
    ofstream output(output_file.c_str());

    output << tour_distance << endl;

    for (int i = 0; i < (int)city_order.size(); i++){
        output << city_order[i] << endl;
    }
    output.close();
}

int distance(city city1, city city2){
    double x = pow(city2.x_pos - city1.x_pos, 2);
    double y = pow(city2.y_pos - city1.y_pos, 2);
    double z = sqrt(x + y);

    return (int)round(z);
}

void nearest(int start, int &tour_distance, string output_file, vector <city> &city_data, vector <int> &city_order){
    int temp_distance;
    int min_distance;
    int current;
    int next;

    cout << endl << "City: " << start << endl;
    current = start;
    city_order.push_back(city_data[start].id);
    city_data[start].visit = 1;

    //iterate through all of the nearest neighbors
    for (int i = 0; i < (int)city_data.size() - 1; i++){
        min_distance = INT_MAX;
        for (int j = 0; j < (int)city_data.size(); j++){
            if (city_data[j].visit == 0){
                temp_distance = distance(city_data[current], city_data[j]);
                if (temp_distance < min_distance){
                    min_distance = temp_distance;
                    next = j;
                }
            }
        }
        //add the shortest distance and make the next city the current city
        tour_distance += min_distance;
        city_order.push_back(city_data[next].id);
        city_data[next].visit = 1;
        current = next;
    }
    min_distance = distance(city_data[current], city_data[start]);
    tour_distance += min_distance;

    cout <<"Nearest neighbour:  " << tour_distance;

    if (tour_distance < best_distance){
        output(output_file, tour_distance, city_order);
        best_distance = tour_distance;
        cout << " (new best path)" << endl;
    } else {
        cout << endl;
    }
}

void two_opt(int &tour_distance, string output_file, vector <city> &city_data, vector <int> &city_order){
    int old_distance = INT_MAX;
    int opt_distance;
    int size = (int)city_order.size();

    int opt_change;
    int tour_change;
    int iteration = 0;

    while (old_distance != tour_distance){
        old_distance = tour_distance;
        for (int i = 0; i < size - 1; i++){
            opt_distance = 0;
            for (int k = i + 1; k < size; k++){
                opt_change = 0;
                tour_change = 0;

                //calculates the new distance for 2-opt swap
                if (i > 0){
                    opt_change += distance(city_data[city_order[i - 1]], city_data[city_order[k]]);
                    tour_change += distance(city_data[city_order[i - 1]], city_data[city_order[i]]);
                }
                if (k < size - 1){
                    opt_change += distance(city_data[city_order[i]], city_data[city_order[k + 1]]);
                    tour_change += distance(city_data[city_order[k]], city_data[city_order[k + 1]]);
                }
                if ((i == 0) && (k != size - 1)){
                    opt_change += distance(city_data[city_order[size - 1]], city_data[city_order[k]]);
                    tour_change += distance(city_data[city_order[size - 1]], city_data[city_order[0]]);
                }
                if ((k == size - 1) && (i != 0)){
                    opt_change += distance(city_data[city_order[i]], city_data[city_order[0]]);
                    tour_change += distance(city_data[city_order[size - 1]], city_data[city_order[0]]);
                }
                opt_distance = tour_distance - tour_change + opt_change;

                if (opt_distance < tour_distance){
                    tour_distance = opt_distance;

                    reverse(city_order.begin() + i, city_order.begin() + k + 1);
                }
            }
        }
        if (old_distance != tour_distance){
            cout << "2-opt iteration " << iteration << ": " << tour_distance;
            iteration++;

            if (tour_distance < best_distance){
                output(output_file, tour_distance, city_order);
                best_distance = tour_distance;
                cout << " (new best path)" << endl;
            } else {
                cout << endl;
            }
        }
    }
}
