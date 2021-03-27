#ifndef __COSANBO_H_INCLUDED__
#define __COSANBO_H_INCLUDED__
#include <string>
namespace cosan
{
    class CosanBO
    {
    public:
        CosanBO();
        virtual ~CosanBO();

        virtual CosanBO *shallow_copy() const;
        virtual CosanBO *deep_copy() const;

        virtual const std::string  get_name() const = 0;

        virtual bool save_file(const std::string &path ,const std::string & prefix = "");
        virtual bool load_file(const std::string &path);
        void print_model();
        virtual bool equals(CosanBO* other, float accuracy = 0.0);
        virtual CosanBO* clone();

    };


}

#endif
