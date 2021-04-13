
### General Questions:

* input accept vector or matrix, only eigen::matrix or std::vector<std::vector<>>
* input validations, type checking, length checking, etc.
* define templates/concepts: categorical, numerical, isComputable, etc.
* sklearn functions perform differently if X is sparse



### Preprocessing

```

namespace preprocessing {
    // ...
}


class Preprocessor {
public:

    /*
     * == sklearn.preprocessing.StandardScaler.fit_transform
     * return: Scaled data has zero mean and unit variance
     */
    eigen::matrix<double> void standardScale(eigen::matrix<double> X) {
        // calculate mean and std on X along all feature axix
        X -= mean;
        X /= scale;
        return X
    }

    /*
     * == sklearn.preprocessing.normalize
     * Normalization is the process of scaling individual samples to have unit norm
     * ??? also accept norm : {'l1', 'l2', 'max'}, default='l2'
     */
    eigen::matrix<double> normalize(eigen::matrix<double> X) {

    }


    enum ImputeStrategy {
        mean, mode, forward, backward, advanced
    };

    /*
     * == sklearn.impute.SimpleImputer.fit_transform
     * impute missing values (??? how are missing values represented, like np.nan)
     */
    eigen::matrix<double> impute(eigen::matrix<double> X, ImputeStrategy strategy) {

    }


    /*
     * == sklearn.preprocessing.OneHotEncoder.fit_transform
     * ??? can X have mixed string and double values
     * ??? how to record categories
     * input: matrix of string
     * return: matrix of double
     */
    eigen::matrix<double> oneHotEncode(eigen::matrix<std::string> x) {

    }


    /*
     * == sklearn.preprocessing.PolynomialFeatures.fit_transform
     */
    eigen::matrix<double> convertToPolynomial(eigen::matrix<double> x, int degree, bool interaction_only) {

    }
    
};

```