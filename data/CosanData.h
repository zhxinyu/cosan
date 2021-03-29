#ifndef __COSANData_H_INCLUDED__
#define __COSANData_H_INCLUDED__
#include <string>
#include <Eigen/Dense>
#include <cosan/io/utils.h>
#include <cosan/base/CosanBO.h>
namespace Cosan
{
    class CosanMatrix: public Eigen::MatrixXd{
    public:
        CosanMatrix(): Eigen::MatrixXd(){}
        template<typename OtherDerived>
        CosanMatrix(const Eigen::MatrixBase<OtherDerived> &other): Eigen::MatrixXd(other){}

        template<typename OtherDerived>
        CosanMatrix & operator=(const Eigen::MatrixBase <OtherDerived>& other){
            this->Eigen::MatrixXd::operator=(other);
            return *this;
        }

    } ;
    class CosanData: public CosanBO{
        public:
            CosanData()=delete;
            CosanData(const std::string & srcX):CosanBO(){
                SetInput(srcX);
            }
            CosanData(const std::string & srcX,
                    const std::string & srcY):CosanBO(){
                SetInput(srcX);
                SetTarget(srcY);
            }
    //        virtual ~CosanBO();
            void SetInput(const std::string & srcX){
                X = load_csv<Eigen::MatrixXd>(srcX);
            }

            void SetTarget(const std::string & srcY){
                Y = load_csv<Eigen::MatrixXd>(srcY);
            }
            CosanMatrix & GetInput(){
                return X;
            }
            const CosanMatrix & GetTarget() const{
                return Y;
            }

//        virtual CosanBO *Shallow_copy() const;
//        virtual CosanBO *Deep_copy() const;

        virtual const std::string  GetName() const {return "Raw Data Object.";}

//        virtual bool SaveFile(const std::string &path ,const std::string & prefix = "");
//        virtual bool LoadFile(const std::string &path);
//        void PrintModel();
//        virtual bool Equals(CosanBO* other, float accuracy = 0.0);
//        virtual CosanBO* Clone();

        protected:
            CosanMatrix X;
            CosanMatrix Y;
    };

//    class Parameter:public CosanMatrix {
//    public:
//        Parameter():CosanMatrix(){}
//    };
//    class Feature:public CosanMatrix {
//    public:
//        Feature():CosanMatrix(){}
//    };
//    class Response : public CosanMatrix {
//        public:
//            Response() : CosanMatrix() {}
//
//    };

}

#endif
