//
// Created by Xinyu Zhang on 4/6/21.
//

#ifndef COSAN_TIMESERIESSPLIT_H
#define COSAN_TIMESERIESSPLIT_H

#include <cosan/selection/splitter.h>
namespace Cosan{
    class TimeSeriesSplit: public Splitter {
        public:
            TimeSeriesSplit()=delete;
            TimeSeriesSplit(gsl::index nrows, gsl::index kfoldnumber =5): Splitter(){
                if (nrows<=kfoldnumber){
                    throw SmallRows;}
                fmt::print("*********************************\n");
                fmt::print("Begin Time Series Splitting!!\n");

                KFoldNumber= kfoldnumber;
                std::vector <gsl::index> idx(nrows);
                std::iota(idx.begin(), idx.end(), 0);
                gsl::index foldSize = nrows/(kfoldnumber+1);
                for (gsl::index i = 1; i<=kfoldnumber;i++){
//                    std::vector<gsl::index> trainidx = std::vector<gsl::index>(idx.begin(), idx.begin()+foldSize*i+nrows%(kfoldnumber+1));
//                    std::vector<gsl::index> testidx  = std::vector<gsl::index>(idx.begin()+foldSize*i+nrows%(kfoldnumber+1), idx.begin()+foldSize*(1+i)+nrows%(kfoldnumber+1));
//                    split_batch.push_back({trainidx,testidx});
                    split_batch.push_back({ std::vector<gsl::index>(idx.begin(), idx.begin()+foldSize*i+nrows%(kfoldnumber+1)),
                                            std::vector<gsl::index>(idx.begin()+foldSize*i+nrows%(kfoldnumber+1), idx.begin()+foldSize*(1+i)+nrows%(kfoldnumber+1))});
                    fmt::print("Current Index is {:}, trainidx size:{:}, testidx size:{:}\n",
                               i-1,foldSize*i+nrows%(kfoldnumber+1),foldSize);
                }
                fmt::print("End Time Series Splitting!!\n");
                fmt::print("*********************************\n");
            }

           std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > GetSplit() {return split_batch;}
        private:
            gsl::index KFoldNumber;
            std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_batch;

    };

    class TimeSeriesSplitParallel: public Splitter {
    public:
        TimeSeriesSplitParallel()=delete;
        TimeSeriesSplitParallel(gsl::index nrows, gsl::index kfoldnumber =5): Splitter(){
            if (nrows<=kfoldnumber){
                throw SmallRows;}
            KFoldNumber = kfoldnumber;
            std::vector <gsl::index> idx(nrows);
            std::iota(idx.begin(), idx.end(), 0);
            gsl::index foldSize = nrows/(kfoldnumber+1);
//            std::mutex mylock;
            fmt::print("*********************************\n");
            fmt::print("Begin Time Series Splitting in Parallel!!\n");
            split_batch.resize(kfoldnumber);
            #pragma omp parallel
            #pragma omp for
            for (gsl::index i = 1; i<=kfoldnumber;i++){
//                    std::vector<gsl::index> trainidx = std::vector<gsl::index>(idx.begin(), idx.begin()+foldSize*i+nrows%(kfoldnumber+1));
//                    std::vector<gsl::index> testidx  = std::vector<gsl::index>(idx.begin()+foldSize*i+nrows%(kfoldnumber+1), idx.begin()+foldSize*(1+i)+nrows%(kfoldnumber+1));
//                    split_batch.push_back({trainidx,testidx});
//                mylock.lock();
                fmt::print("Current Index is {:}, the current thread num is {:}, total number of threads {:}. trainidx size:{:}, testidx size:{:}\n",
                           i-1, omp_get_thread_num(),omp_get_num_threads(),foldSize*i+nrows%(kfoldnumber+1),foldSize);
                split_batch[i-1]={ std::vector<gsl::index>(idx.begin(), idx.begin()+foldSize*i+nrows%(kfoldnumber+1)),
                                        std::vector<gsl::index>(idx.begin()+foldSize*i+nrows%(kfoldnumber+1), idx.begin()+foldSize*(1+i)+nrows%(kfoldnumber+1))};
//                mylock.unlock();
            }

            fmt::print("End Time Series Splitting in Parallel!!\n");
            fmt::print("*********************************\n");
        }

        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > GetSplit() {return split_batch;}
    private:
        gsl::index KFoldNumber;
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_batch;

    };
}

#endif //COSAN_TIMESERIESSPLIT_H
