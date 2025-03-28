#include <iostream>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

//g++ -o eigen met_potencia.cpp -std=c++11 -I Eigen compilar


//Ej: [[2, -1, 0], [-1, 2, -1], [0, -1, 2]] filas
//autovalores: 1, 2, 3
//autovectores: [1,1,1], [1,0,-1], [1, -2, 1]


Eigen::MatrixXd leerMatriz(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"No se puedo abrir"<<endl;
        exit(1);
    }
    int fil, col;
    file >> fil >> col;
    Eigen::MatrixXd matriz(fil, col);

    for(int i = 0; i < fil; i++){
        for(int j = 0; j < col; j++){
            file >> matriz(i, j);
        }
    }
    file.close();
    return matriz;
}

tuple<double, Eigen::VectorXd, int> power_iteration(const Eigen::MatrixXd A, int niter=10000,double eps = 1e-7){

    Eigen::VectorXd v = Eigen::VectorXd::Random(A.cols());
    int indice = 0;
    double a = 1;
    Eigen::VectorXd v_viejo = v;
    for(int i=0; i < niter;i++){
        v_viejo = v;
        
        Eigen::VectorXd  dot = A * v;
        
        v = dot / dot.norm();
        
        a = (v.dot(A * v)) / v.transpose().dot(v) ;
        
        indice++;
        
        Eigen::VectorXd vec = v - v_viejo;

        if (vec.cwiseAbs().maxCoeff() < eps) {
            break;
        }
        
    }

    return make_tuple(a, v, indice);
}

tuple<Eigen::VectorXd, Eigen::MatrixXd, Eigen::VectorXd> eigen(Eigen::MatrixXd A, int niter = 10000, double eps = 1e-7){
    Eigen::VectorXd eigenvalues(A.rows()); //Es feo no inicializarlo deberia ser vacio
    Eigen::VectorXd convergencia(A.rows());
    Eigen::MatrixXd eigenvectors(A.rows(), A.rows()); //

    for(int i = 0; i < A.rows(); i++){
        tuple<double, Eigen::VectorXd, int> result = power_iteration(A, niter, eps);
        double a = std::get<0>(result);
        Eigen::VectorXd v = std::get<1>(result);
        eigenvalues(i) = a;
        convergencia(i) = std::get<2>(result);
        eigenvectors.col(i) = v; 

        A = A - a*(v*v.transpose());
    }
    return make_tuple(eigenvalues, eigenvectors, convergencia);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <matrix_file>" << endl;
        return 1;
    }

    const string filename = argv[1];
    Eigen::MatrixXd A = leerMatriz(filename);

    std::tuple<Eigen::VectorXd, Eigen::MatrixXd, Eigen::VectorXd> result = eigen(A);
    Eigen::VectorXd eigenvalues = std::get<0>(result);
    Eigen::MatrixXd eigenvectors = std::get<1>(result);
    Eigen::VectorXd convergencia = std::get<2>(result);

    
    
    for (int i = 0; i < convergencia.size(); i++) {
        cout<<convergencia[i]<<" ";
    }

    cout<<"\n";
    
    for (int i = 0; i < eigenvalues.size(); i++) {
        cout<<eigenvalues[i]<<" ";
    }

    cout<<"\n"<< eigenvectors;
    return 0;
}
