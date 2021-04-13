//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_OVERUNDERFLOW_H
#define COSAN_OVERUNDERFLOW_H
#include <cosan/preprocessing/preprocessor.h>
namespace Cosan{
    /**
     * Clean up row with underflow or overflow data enty.
     *
     */
    template<Numeric NumericType>
    class OverUnderFlow: public Preprocessor<NumericType> {
        public:
            OverUnderFlow() = delete;
            OverUnderFlow( CosanRawData<NumericType> & RD):Preprocessor<NumericType>(){
                this->fit(RD);
            }

        private:
            void fit(CosanRawData<NumericType>& RD) {
                fmt::print("*********************************\n");
                fmt::print("Begin cleaning up data of overflow/underflow!\n");

                std::set<gsl::index> InfIdx;
                for (auto & each: RD.GetIdxpinfX()){
                    InfIdx.insert(each[0]);
                }
                for (auto & each:  RD.GetIdxminfX()){
                    InfIdx.insert(each[0]);
                }
                for (auto & each: RD.GetIdxpinfY()){
                    InfIdx.insert(each[0]);
                }
                for (auto & each: RD.GetIdxminfY()){
                    InfIdx.insert(each[0]);
                }
                std::vector<gsl::index> SelectedIdx;
                for (auto i = 0; i<RD.GetrowsX();i++){
                    if (InfIdx.find(i)==InfIdx.end()){
                        SelectedIdx.push_back(i);
                    }
                }
                fmt::print("There are {:d} rows that have overflow/underflow data! Delete the whole rows. \n",InfIdx.size());
                if (RD.GetTarget().size()==0){
                    RD.UpdateData(RD.GetInput()(SelectedIdx,Eigen::all));
                }
                else{
                    RD.UpdateData(RD.GetInput()(SelectedIdx,Eigen::all),RD.GetTarget()(SelectedIdx,Eigen::all));
                }

                gsl::index NumOfCat  = RD.GetcolCatX().size();
                fmt::print("End of cleaning up data of overflow/underflow!\n");
                fmt::print("*********************************\n");
                if (NumOfCat==0){
                    return ;
                }
                std::vector<std::string> svaluesX;
                std::vector<std::string> svaluesY;
                for (gsl::index i=0; i< RD.GetsvaluesX().size();i++){
                    if (InfIdx.find(i/NumOfCat)==InfIdx.end()){
                        svaluesX.push_back(RD.GetsvaluesX().at(i));
                    }
                }
                RD.UpdateCat(svaluesX);

            }

    };
}

#endif //COSAN_OVERUNDERFLOW_H
