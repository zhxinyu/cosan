//
// Created by Xinyu Zhang on 4/6/21.
//

#ifndef COSAN_RANDOMKFOLD_H
#define COSAN_RANDOMKFOLD_H

#include <cosan/selection/splitter.h>

namespace Cosan{
    class RandomKFold: public Splitter {
    public:
        RandomKFold() = delete;
        RandomKFold(gsl::index nrows,gsl::index kfoldnumber=5):Splitter(nrows,kfoldnumber){
            KFoldNumber = kfoldnumber;
            std::vector<gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows/kfoldnumber;
            for (gsl::index i = 0;i<kfoldnumber;i++){
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
        gsl::index KFoldNumber;
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_batch;
    };

    class RandomKFoldParallel: public Splitter {
    public:
        RandomKFoldParallel()=delete;
        RandomKFoldParallel(gsl::index nrows,gsl::index kfoldnumber=5):Splitter(nrows,kfoldnumber){
            KFoldNumber = kfoldnumber;
            std::vector<gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows/kfoldnumber;
//            std::mutex mylock;
            split_batch.resize(kfoldnumber);
            #pragma omp parallel
            #pragma omp for
            for (gsl::index i = 0;i<kfoldnumber;i++){
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
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > GetSplit()  {return split_batch;}
    private:
        gsl::index KFoldNumber;
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_batch;
    };
}

#endif //COSAN_RANDOMKFOLD_H
