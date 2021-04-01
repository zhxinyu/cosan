//#ifndef __COSANData_H_INCLUDED__
//#define __COSANData_H_INCLUDED__
//
//#include <string>
//#include "../base/common.h"
//#include "../io/csvLoader.h"
//#include "../base/CosanBO.h"
//
//namespace Cosan {
//    class CosanMatrix : public Eigen::MatrixXd {
//    public:
//        CosanMatrix() : Eigen::MatrixXd() {}
//
//        template<typename OtherDerived>
//        CosanMatrix(const Eigen::MatrixBase<OtherDerived> &other): Eigen::MatrixXd(other) {}
//
//        template<typename OtherDerived>
//        CosanMatrix &operator=(const Eigen::MatrixBase<OtherDerived> &other) {
//            this->Eigen::MatrixXd::operator=(other);
//            return *this;
//        }
//
//    };
//
//    class CosanData : public CosanBO {
//    public:
//        CosanData() = delete;
//
//        CosanData(const std::string &srcX) : CosanBO() {
//            SetInput(srcX);
//        }
//
//        CosanData(const std::string &srcX,
//                  const std::string &srcY) : CosanBO() {
//            SetInput(srcX);
//            SetTarget(srcY);
//        }
//
//        //        virtual ~CosanBO();
//        void SetInput(const std::string &srcX) {
//            X = load_csv<Eigen::MatrixXd>(srcX);
//        }
//
//        void SetTarget(const std::string &srcY) {
//            Y = load_csv<Eigen::MatrixXd>(srcY);
//        }
//
//        CosanMatrix &GetInput() {
//            return X;
//        }
//
//        const CosanMatrix &GetTarget() const {
//            return Y;
//        }
//
//        virtual const std::string GetName() const { return "Raw Data Object."; }
//
//    protected:
//        CosanMatrix X;
//        CosanMatrix Y;
//    };
//
//
//}
//
//#endif
