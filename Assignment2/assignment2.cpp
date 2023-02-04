#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

// function for calculating sum of a vector
double sum_vector(vector<double> v)
{
    return accumulate(v.begin(), v.end(), 0.0);
}
// funtion for calculating mean of a vector
double mean_vector(vector<double> v)
{
    return sum_vector(v) / v.size();
}

// function for calculating median of a vector
double median_vector(vector<double> v)
{
    sort(v.begin(), v.end());
    int n = v.size();
    if (n % 2 == 0)
        return (v[n / 2 - 1] + v[n / 2]) / 2;
    else
        return v[n / 2];
}
// function for calculating range of a vector
double range_vector(vector<double> v)
{
    double min_v = *min_element(v.begin(), v.end());
    double max_v = *max_element(v.begin(), v.end());
    return max_v - min_v;
}
// function for calculating covariance of two vectors
double covariance(vector<double> v1, vector<double> v2)
{
    double mean_v1 = mean_vector(v1), mean_v2 = mean_vector(v2);
    double cov = 0.0;
    int n = v1.size();
    for (int i = 0; i < n; i++)
        cov += (v1[i] - mean_v1) * (v2[i] - mean_v2);
    return cov / n;
}
// function for calculating correlation of two vectors
double correlation(vector<double> v1, vector<double> v2)
{
    double cov = covariance(v1, v2);
    double stddev_v1 = sqrt(covariance(v1, v1));
    double stddev_v2 = sqrt(covariance(v2, v2));
    return cov / (stddev_v1 * stddev_v2);
}
// function for printing statistics of a vector
void print_stats(vector<double> v)
{
    cout << "sum: " << sum_vector(v) << endl;
    cout << "mean: " << mean_vector(v) << endl;
    cout << "median: " << median_vector(v) << endl;
    cout << "range: " << range_vector(v) << endl;
}
// main function
int main()
{
    // read data from file function kindly provided by Dr. Mazidi
    ifstream inFS;
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN), medv(MAX_LEN);

    inFS.open("Boston.csv");
    if (!inFS.is_open())
    {
        cout << "Could not open file Boston.csv." << endl;
        return 1;
    }
    cout << " --------------------- " << endl;
    cout << "Reading line 1" << endl;
    getline(inFS, line);
    cout << "heading: " << line << endl;

    int numObservation = 0;
    while (inFS.good())
    {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservation) = stof(rm_in);
        medv.at(numObservation) = stof(medv_in);

        numObservation++;
    }
    rm.resize(numObservation);
    medv.resize(numObservation);

    cout << "new length: " << rm.size() << endl;
    cout << "Closing file Boston.csv." << endl;
    inFS.close();

    cout << "Number of records: " << numObservation << endl;
    cout << " --------------------- " << endl;
    cout << "rm: " << endl;
    print_stats(rm);
    cout << " --------------------- " << endl;
    cout << "medv: " << endl;
    print_stats(medv);
    cout << " --------------------- " << endl;
    cout << "covariance: " << covariance(rm, medv) << endl;
    cout << "correlation: " << correlation(rm, medv) << endl;
    cout << " --------------------- " << endl;

    return 0;
}
