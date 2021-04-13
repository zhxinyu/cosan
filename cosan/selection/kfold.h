//
// Created by Xinyu Zhang on 4/6/21.
//
// TODO: omp_set_num_threads()
#ifndef COSAN_KFOLD_H
#define COSAN_KFOLD_H
#include <cosan/selection/selection.h>
namespace Cosan {
    /**
     * https://en.wikipedia.org/wiki/Cross-validation_(statistics)
     */
    class KFold : public Splitter {
    public:
        KFold() : Splitter() {}
        KFold(gsl::index kfoldnumber) : Splitter(kfoldnumber) {}
        KFold(gsl::index nrows, gsl::index kfoldnumber): Splitter(nrows,kfoldnumber){}
        void SetSplit(gsl::index nrows) {
            if (nrows <= KFoldNumber) {
                throw SmallRows;
            }
            std::vector <gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows / KFoldNumber;
            for (gsl::index i = 0; i < KFoldNumber; i++) {
                std::vector <gsl::index> testidx(foldSize), trainidx;
                if (i == KFoldNumber - 1) {
                    testidx.resize(nrows - i * foldSize);
                }
                fmt::print("Current Index is {:}, trainidx size:{:}, testidx size:{:}\n",
                           i, nrows - foldSize, foldSize);
                std::iota(testidx.begin(), testidx.end(), i * foldSize);
                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
                                    std::inserter(trainidx, trainidx.begin()));

                split_batch.push_back({trainidx, testidx});

            }
        }

//        void SetSplit(gsl::index nrows,gsl::index kfoldnumber = KFoldNumber ){
//            if (nrows<=kfoldnumber){
//                throw SmallRows;
//            }
//            KFoldNumber = kfoldnumber;
//            std::vector<gsl::index> idx(nrows);
//            std::iota(idx.begin(), idx.end(), 0);
//            gsl::index foldSize = nrows/kfoldnumber;
//            for (gsl::index i = 0;i<kfoldnumber;i++){
//                std::vector<gsl::index> testidx(foldSize),trainidx;
//                if (i==kfoldnumber-1){
//                    testidx.resize(nrows-i*foldSize);
//                }
//                fmt::print("Current Index is {:}, trainidx size:{:}, testidx size:{:}\n",
//                           i,nrows-foldSize,foldSize);
//                std::iota(testidx.begin(), testidx.end(), i*foldSize);
//                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
//                                    std::inserter(trainidx, trainidx.begin()));
//
//                split_batch.push_back({trainidx,testidx});
//
//            }
//        }
        std::vector <std::tuple<std::vector < gsl::index>, std::vector<gsl::index>> > &

        GetSplit() { return split_batch; }

    private:
        std::vector <std::tuple<std::vector < gsl::index>, std::vector<gsl::index>> >
        split_batch;
    };

//    class KFoldParallel : public Splitter {
//    public:
//        KFoldParallel() : Splitter() {
//            KFoldNumber = 5;
//        }
//
//        KFoldParallel(gsl::index kfoldnumber) : Splitter() {
//            KFoldNumber = kfoldnumber;
//        }
//
//        KFoldParallel(gsl::index nrows, gsl::index kfoldnumber) : Splitter(nrows, kfoldnumber) {
//            KFoldNumber = kfoldnumber;
//            SetSplit(nrows);
//        }
//
//        void SetSplit(gsl::index nrows) {
//            if (nrows <= KFoldNumber) {
//                throw SmallRows;
//            }
//            std::vector <gsl::index> idx(nrows);
//            std::iota(idx.begin(), idx.end(), 0);
//            gsl::index foldSize = nrows / KFoldNumber;
//#pragma omp parallel for
//            for (gsl::index i = 0; i < KFoldNumber; i++) {
//                std::vector <gsl::index> testidx(foldSize), trainidx;
//                if (i == KFoldNumber - 1) {
//                    testidx.resize(nrows - i * foldSize);
//                }
//                fmt::print("Current Index is {:}, trainidx size:{:}, testidx size:{:}\n",
//                           i, nrows - foldSize, foldSize);
//                std::iota(testidx.begin(), testidx.end(), i * foldSize);
//                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
//                                    std::inserter(trainidx, trainidx.begin()));
//
//                split_batch.push_back({trainidx, testidx});
//
//            }
//        }
//
////        void SetSplit(gsl::index nrows,gsl::index kfoldnumber){
////            if (nrows<=kfoldnumber){
////                throw SmallRows;
////            }
////            KFoldNumber = kfoldnumber;
////            std::vector<gsl::index> idx(nrows);
////            std::iota(idx.begin(), idx.end(), 0);
////            gsl::index foldSize = nrows/kfoldnumber;
////            #pragma omp parallel for
////            for (gsl::index i = 0;i<kfoldnumber;i++){
////                std::vector<gsl::index> testidx(foldSize),trainidx;
////                if (i==kfoldnumber-1){
////                    testidx.resize(nrows-i*foldSize);
////                }
////                fmt::print("Current Index is {:}, trainidx size:{:}, testidx size:{:}\n",
////                           i,nrows-foldSize,foldSize);
////                std::iota(testidx.begin(), testidx.end(), i*foldSize);
////                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
////                                    std::inserter(trainidx, trainidx.begin()));
////
////                split_batch.push_back({trainidx,testidx});
////
////            }
//        std::vector <std::tuple<std::vector < gsl::index>, std::vector<gsl::index>> > &
//
//        GetSplit() { return split_batch; }
//
//    private:
//        std::vector <std::tuple<std::vector < gsl::index>, std::vector<gsl::index>> >
//        split_batch;
//    };

    class KFoldParallel : public Splitter {
    public:
        KFoldParallel() : Splitter() {}
        KFoldParallel(gsl::index kfoldnumber) : Splitter(kfoldnumber) {}
        KFoldParallel(gsl::index nrows, gsl::index kfoldnumber): Splitter(nrows,kfoldnumber){}
        void SetSplit(gsl::index nrows){
            if (nrows <= KFoldNumber) {
                throw SmallRows;
            }
            std::vector <gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows / KFoldNumber;
//            std::mutex mylock;
            split_batch.resize(KFoldNumber);
            #pragma omp parallel for
            for (gsl::index i = 0; i < KFoldNumber; i++) {
                std::vector <gsl::index> testidx(foldSize), trainidx;
                if (i == KFoldNumber - 1) {
                    testidx.resize(nrows - i * foldSize);
                }
                fmt::print(
                        "Current Index is {:}, the current thread num is {:}, total number of threads {:}. trainidx size:{:}, testidx size:{:}\n",
                        i, omp_get_thread_num(), omp_get_num_threads(), nrows - foldSize, foldSize);
                std::iota(testidx.begin(), testidx.end(), i * foldSize);
                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
                                    std::inserter(trainidx, trainidx.begin()));
                split_batch[i] = {trainidx, testidx};
            }
        }
        std::vector <std::tuple<std::vector < gsl::index>, std::vector<gsl::index>> > & GetSplit() { return split_batch; }

    private:
        std::vector <std::tuple<std::vector < gsl::index>, std::vector<gsl::index>> > split_batch;
    };

}


#endif //COSAN_KFOLD_H
