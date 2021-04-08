//
// Created by Xinyu Zhang on 4/6/21.
//

#ifndef COSAN_RANDOMKFOLD_H
#define COSAN_RANDOMKFOLD_H

#include <cosan/selection/selection.h>

namespace Cosan{
    class RandomKFold: public Splitter {
    public:
        RandomKFold() : Splitter() {}
        RandomKFold(gsl::index kfoldnumber) : Splitter(kfoldnumber) {}
        RandomKFold(gsl::index nrows, gsl::index kfoldnumber): Splitter(nrows,kfoldnumber){}
        void SetSplit(gsl::index nrows){
            if (nrows<=KFoldNumber){
                throw SmallRows;
            }
            std::vector<gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows/KFoldNumber;
            for (gsl::index i = 0;i<KFoldNumber;i++){
                std::vector<gsl::index> testidx,trainidx;
                std::sample(idx.begin(), idx.end(), std::back_inserter(testidx),
                            foldSize, std::mt19937{std::random_device{}()});
                std::sort(testidx.begin(),testidx.end());
                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
                                    std::inserter(trainidx, trainidx.begin()));
                fmt::print("Current Index is {:}, trainidx size:{:}, testidx size:{:}\n",
                           i,trainidx.size(),testidx.size());
                split_batch.push_back({trainidx,testidx});
            }
        }

        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > GetSplit()  {return split_batch;}
    private:
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_batch;
    };



    class RandomKFoldParallel: public Splitter {
    public:
        RandomKFoldParallel() : Splitter() {}
        RandomKFoldParallel(gsl::index kfoldnumber) : Splitter(kfoldnumber) {}
        RandomKFoldParallel(gsl::index nrows, gsl::index kfoldnumber): Splitter(nrows,kfoldnumber){}
        void SetSplit(gsl::index nrows){
            if (nrows<=KFoldNumber){
                throw SmallRows;
            }
            std::vector<gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows/KFoldNumber;
//            std::mutex mylock;
            split_batch.resize(KFoldNumber);
            #pragma omp parallel for
            for (gsl::index i = 0;i<KFoldNumber;i++){
                std::vector<gsl::index> testidx,trainidx;
                std::sample(idx.begin(), idx.end(), std::back_inserter(testidx),
                            foldSize, std::mt19937{std::random_device{}()});
                std::sort(testidx.begin(),testidx.end());
                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
                                    std::inserter(trainidx, trainidx.begin()));
                fmt::print("Current Index is {:}, the current thread num is {:}, total number of threads {:}. trainidx size:{:}, testidx size:{:}\n",
                           i, omp_get_thread_num(),omp_get_num_threads(),trainidx.size(),testidx.size());
//                mylock.lock();
                split_batch[i] = {trainidx,testidx};
//                mylock.unlock();
            }
        }

        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > GetSplit() & {return split_batch;}
    private:
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_batch;
    };


}

#endif //COSAN_RANDOMKFOLD_H
