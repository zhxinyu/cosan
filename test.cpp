//
// Created by Xinyu Zhang on 3/26/21.
//

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <fstream>
using namespace Eigen;
using namespace std;

template<typename M>
M load_csv (const std::string & path) {
    ifstream indata;
    indata.open(path);
    string line;
    vector<double> values;
    uint rows = 0;
    while (std::getline(indata, line)) {
        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ',')) {
            values.push_back(stod(cell));
        }
        ++rows;
    }

    return Map<const Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, RowMajor> >(values.data(), rows, values.size()/rows);
}

int main() {
   MatrixXd X = load_csv<MatrixXd>("./data/toy/X.csv");
   MatrixXd y = load_csv<MatrixXd>("./data/toy/y.csv");

//    m(0, 0) = 3;
//    m(1, 0) = 2.5;
//    m(0, 1) = -1;
//    m(1,1)  = m(1,0)+m(0,1);

   cout<<X<<endl;

   cout<<y<<endl;
//
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;
}
