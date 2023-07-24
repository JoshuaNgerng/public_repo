library(ggplot2)
library(DataExplorer)
library(mice)
library(caret)
library(e1071)
library(class)
library(pROC)
library(ROCR)


normalize <- function(x) {
  return ((x - min(x)) / (max(x) - min(x))) 
}

extract_svm <- function(svm_in, test, target){
  pred = predict(svm_in, test)
  cm = table(Predicted = pred, Actual = test_set[, target])
  acc = sum(diag(cm))/sum(cm) * 100
  prec = sum(diag(cm))/sum(colSums(cm)) * 100
  return (c(acc, prec))
}

extract_knn <- function(pred, actual){
  cm = table(Predicted = pred, Actual = test_set[, target])
  acc = sum(diag(cm))/sum(cm) * 100
  prec = sum(diag(cm))/sum(colSums(cm)) * 100
  return (c(acc, prec))
}

compare_roc <- function(target_group, def_model, tuned_model)
{
  par(pty = "s")
  roc(target_group, def_model, plot = TRUE, legacy.axes = TRUE, 
      percent = TRUE, xlab = "False Positive Percentage", 
      ylab="True Postive Percentage", col = "#377eb8", lwd = 4, 
      print.auc = TRUE)
  plot.roc(target_group, tuned_model, percent = TRUE, col="#4daf4a", 
           lwd = 4, print.auc = TRUE, add = TRUE, print.auc.y=40)
  legend("bottomright", legend = c("default", "tuned"), cex = 0.5, 
          col = c("#377eb8", "#4daf4a"), lwd = 4)
  par(pty = "m")
}
# set directory and get data
setwd("C:/Users/USER/Desktop/R_proj/AML/water_quality")
df <- read.csv("water_potability.csv")
dim(df)
summary(df)

# EDA
target <- match("Potability", colnames(df))
plot_histogram(df)
plot_bar(df)
boxplot(df)
table(df[, target])
boxplot(df[, -3])
plot_correlation(df, type=c('continuous'))
plot_missing(df)
sum(is.na(df))


# clean data
imp = mice(data = df, m = 5, maxit = 20)
df <- complete(imp, 5)

# adjust target 
df$Potability = factor(df$Potability, levels = c(0, 1))

#make this example reproducible
set.seed(1)

#use 70% of dataset as training set and 30% as test set
sample <- sample(c(TRUE, FALSE), nrow(df), replace = TRUE, prob = c(0.7,0.3))
train_set  <- df[sample, ]
test_set   <- df[!sample, ]
y_train <- train_set[, target]
x_train <- train_set[, -target]
y_test <- test_set[, target]
x_test <- test_set[, -target]

# KNN
n_train_set <- as.data.frame(lapply(train_set[1:9], normalize))
n_test_set <- as.data.frame(lapply(test_set[1:9], normalize))
def_knn <- knn(train = n_train_set, test = n_test_set,
                cl = y_train, k = 1)
eval_def_knn <- extract_knn(def_knn, y_test)

# tune to find best parameter
tuned_model_knn = tune.knn(x_train, y_train, k = 1:10,
                       tunecontrol = tune.control(sampling = "boot"))
summary(tuned_model)
best_knn <- knn(train = n_train_set, test = n_test_set,
                cl = y_train, k = 9)
eval_best_knn <- extract_knn(best_knn, y_test)
compare_roc(y_test, as.ordered(def_knn), as.ordered(best_knn))

# SVM
# make SVM using default radial method
def_svm <- svm(Potability ~ ., data = train_set, kernel = "radial")
eval_def_svm <- extract_svm(def_svm, test_set, target)

# tune to find best parameter
tuned_model_SVM = tune(svm, Potability ~ ., data = train_set,
                   ranges = list(epsilon = seq (0, 1, 0.1), 
                                 cost = 2 ^ (0:2), 
                                 kernel = c("radial", "linear", "poly"), 
                   tunecontrol = tune.control(nrepeat = 10, sampling = "cross", 
                                              cross = 10)))
opt_model_k = tuned_model_SVM$best.model
opt_model_k$epsilon
best_svm <- svm(Potability ~ ., data = train_set, kernel = "radial", 
                epsilon = 0, cost = 2)
eval_best_svm <- extract_svm(best_svm, test_set, target)
compare_roc(as.ordered(y_test), as.ordered(predict(def_svm, test_set)), 
            as.ordered(predict(best_svm, test_set)))
            

# RF
def_RF <- randomForest(Potability ~ ., data = train_set, proximity = TRUE)
eval_def_RF <- extract_svm(def_RF, test_set, target)

#tune rf
tuned_model_RF <- tuneRF(x_train, y_train, stepFactor = 0.5, 
                         plot = TRUE, ntreeTry = 100, 
                         trace = TRUE, improve = 0.05)
best_RF <- randomForest(Potability ~ ., data = train_set, mtry = 6, 
                        ntreeTry = 200, proximity = TRUE)
compare_roc(as.ordered(y_train), as.ordered(def_RF$votes[, 1]), 
            as.ordered(best_RF$votes[, 1]))
