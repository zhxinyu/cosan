### Things to figure out
1. model type
2. dataset type

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
  
  // hyper-parameter tuning
  <T> grid_search(<T> grid,<model type> model, <T> x_train, <T> y_train, <T> x_test, <T> y_test, <not_sure> metric){
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
  
  // cross validation
  
  
  
};
```
