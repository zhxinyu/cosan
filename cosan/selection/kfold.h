//
// Created by Xinyu Zhang on 4/6/21.
//

#ifndef COSAN_KFOLD_H
#define COSAN_KFOLD_H
#include <cosan/selection/splitter.h>
namespace Cosan{
    class KFold: public Splitter {
    public:
        KFold(gsl::index nrows,gsl::index kfoldnumber=5):Splitter(){
            if (nrows<kfoldnumber){
                throw SmallRows;
            }
            std::vector<gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows/kfoldnumber;
            for (gsl::index i = 0;i<kfoldnumber;i++){
                std::vector<gsl::index> testidx(foldSize),trainidx;
                if (i==kfoldnumber-1){
                    testidx.resize(nrows-i*foldSize);
                }
                fmt::print("Current Index is {:}, trainidx size:{:}, testidx size:{:}\n",
                           i,nrows-foldSize,foldSize);
                std::iota(testidx.begin(), testidx.end(), i*foldSize);
                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
                                    std::inserter(trainidx, trainidx.begin()));

                split_batch.push_back({trainidx,testidx});

            }
        }
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > GetSplit()  {return split_batch;}
    private:
        gsl::index kfoldnumber;
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_batch;
    };


    class KFoldParallel: public Splitter {
    public:
        KFoldParallel(gsl::index nrows,gsl::index kfoldnumber=5):Splitter(){
            if (nrows<kfoldnumber){
                throw SmallRows;
            }
            KFoldNumber = kfoldnumber;
            std::vector<gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows/kfoldnumber;
//            std::mutex mylock;
            split_batch.resize(kfoldnumber);
            #pragma omp parallel
            #pragma omp for
            for (gsl::index i = 0;i<kfoldnumber;i++){
                std::vector<gsl::index> testidx(foldSize),trainidx;
                if (i==kfoldnumber-1){
                    testidx.resize(nrows-i*foldSize);
                }
                fmt::print("Current Index is {:}, the current thread num is {:}, total number of threads {:}. trainidx size:{:}, testidx size:{:}\n",
                           i, omp_get_thread_num(),omp_get_num_threads(),nrows-foldSize,foldSize);
                std::iota(testidx.begin(), testidx.end(), i*foldSize);
                std::set_difference(idx.begin(), idx.end(), testidx.begin(), testidx.end(),
                                    std::inserter(trainidx, trainidx.begin()));
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


#endif //COSAN_KFOLD_H
