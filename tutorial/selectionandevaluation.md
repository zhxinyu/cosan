# Tutorial

### Things to fig
1. model type
2. dataset type: 
    1. example: https://github.com/scikit-learn/scikit-learn/blob/95119c13af77c76e150b753485c662b7c52a41a2/sklearn/preprocessing/_data.py#L84
3. need a check_is_array function, where should we put it?
3. comment format
4. how to tune hyperparameters if a model has multiple hyper-parameters?  

### Model Selection and Evaluation Design

```
class model_select_evaluate{

  // for max error
  double error_num(<T> y_true, <T> y_predict){
    // matrix subtraction
    y_diff = y_true - y_predict
    
    // return number of elements in y_diff that are larger than 0
    return y_diff>0;
  };
  
  // for absolute error mean 
  double abs_error(<T> y_true, <T> y_predict){
  
  }
  
  // for mse mean
  double mse_mean(<T> y_true, <T> y_predict){
  
  }
  
  // R^2 
  double r2_error(<T> y_true, <T> y_predict){
  
  }
  
  // split a data set with a given ratio
  list<eigen matrix> split(<eigen matrix> x, <eigen matrix> y, ratio, random_state){
      ind_train = x.length * ratio
      x_train, x_test = x[:ind_train], x[ind_train+1:]
      // do the same for y
      return [x_train, y_train, x_test, y_test]
  }
  
  /* split dataset for cross validation
     Input: 
           test_ind: index of the fold that is used as testing set
           group_n: the number of group we are dividing the dataset into
  */
  list<eigen matrix> split_cv(<eigen matrix> x, <eigen matrix> y, int group_n, int test_ind){
      // split the data set into group_n groups
      
      // pick the test_ind th group as the testing group
      
      // concatenate the rest as the training group
      return [x_train, y_train, x_test, y_test]
  }
  
  /* hyper-parameter tuning
    input: 
          grid: array-like iterable of shape (m,n), where m is the number of hyperparameters 
                and n is the number of potential values for one hyperparameter
          model: a model that needs hyperparameter tuning
          x: array-like iterable ? of shape (n_samples, n_features)
          y: array-like iterable ? of shape (n_labels)
          metric, a error measuring function        
    output: array-like iterable of shape (m,1), the set of hyperparameter that gives the best result
  */
  <T> grid_search(<T> grid,<model type> model, <T> x, <T> y, <not_sure> metric){
     // check data type and convert them into eigen matrix here
     
     // split the dataset into training and testing 
     x_train, y_train, x_test, y_test = split(x, y, ratio=3:1, random=0)
  
     min_err = inf;
     best_para = 0;
     
     // evaluate each potential hyper-parameter value
     for each in grid:
        model.create(each)
        model.fit(x_train, y_train)
        y_predict = model.predict(x_test)
        error = metric(y_test, y_predict)
        if error < min_err:
          min_error = error
          best_para = each
          
      return best_para
  }
  
  /* cross validation
        Output: double, the averaged error from each cv iteration
  */

     double cv(<model type> model, <T> x, <T> y, int fold, <not sure> metric){
    // potentially replace for loop with parallel processing
    list<double> or <eigen matrix> errors = []

    std::vector< std::tuple(std::vector<int>,std::vector<int>) > > train_batch = split_cv(x.rows(), fold);

    for (auto& [train_idx,test_idx]: train_batch) :

        x_train, y_train, x_test, y_test = x(train_idx,Eigen::all),y(train_idx,Eigen::all),x(test_idx,Eigen::all),y(test_idx,Eigen::all);
        model.fit(x_train, y_train)
        y_predict = model.predict(x_test)
        error = metric(y_test, y_predict)
        errors.add(error)
    return mean(error)
  }
  
};
};

  
};
```
