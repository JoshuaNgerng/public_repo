from PIL import Image, ImageOps
from sklearn import metrics
from skimage.feature import local_binary_pattern
from sklearn.svm import LinearSVC
import joblib
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import glob, os
import time

def	load_indiv_img(root, mode, defect, name):
	p = os.path.join(root, mode, defect)
	os.chdir(p)
	img = np.asarray(Image.open(name))
	if img.ndim == 3:
		img = ImageOps.grayscale(img)
	return (img, defect)

# load all image into alist
def load_all_img(root, mode):
	img_data = []
	label_data = []
	t = ["Crazing", "Inclusion", "Patches", "Pitted", "Rolled", "Scratches"]
	num = 0
	for i in range(len(t)):
		p = os.path.join(root, mode, t[i])
		os.chdir(p)
		for file in glob.glob("*.bmp"):
			img = np.asarray(Image.open(file))
			if img.ndim == 3:
				img = ImageOps.grayscale(img)
			img_data.append(img)
			label_data.append(i)
			num += 1
	print(f"there are {num} total images loaded")
	return (img_data, label_data)

# compute local binary pattern 
def compute_lbp(img, radi = 3):
	output = []
	n = radi * 8
	for	i in range(len(img)):
		lbp = local_binary_pattern(img[i], n, radi, "uniform")
		lbp = lbp.ravel()
		feature = np.zeros(int(lbp.max() + 1))
		for i in lbp:
			feature[int(i)] += 1
		feature /= np.linalg.norm(feature, ord = 1)
		output.append(feature)
	return (output)

def hist(ax, lbp):
    n_bins = int(lbp.max() + 1)
    return ax.hist(lbp.ravel(), density=True, bins=n_bins, range=(0, n_bins),
            		facecolor='0.5')

# plot histograms of LBP of textures
def analyze_lbp_hist(img, names, radi = 3):
	c = len(names)
	n = 8 * radi
	fig, ax_hist = plt.subplots(nrows = 1, ncols = c, figsize=(9, 5))
	plt.gray()

	for ax, name, i in zip(ax_hist, names, range(c)):
		img_lbp = local_binary_pattern(img[i], n, radi, "uniform")
		counts, _, bars = hist(ax, img_lbp)
		ax.set_ylim(top = np.max(counts[:-1]))
		ax.set_xlim(right = n + 2)
		ax.set_title(name)

	ax_hist[0].set_ylabel('Percentage')
	plt.show()

#eval model
def eval_model(model, actual, input, radi = 3):
	start = time.time()
	lbp = compute_lbp(input, radi)
	predic = model.predict(lbp)
	end = time.time()
	print(f"The prediction time is {end - start}s")

	# make confusion matrix for analysis
	labels = ["Crazing", "Inclusion", "Patches", "Pitted", "Rolled", "Scratches"]
	c_mat = metrics.confusion_matrix(actual, predic)
	s = sns.heatmap(c_mat, annot = True, xticklabels = labels, yticklabels = labels)
	s.set(xlabel = 'Predicted', ylabel = 'Actual')
	actual = np.array(actual)
	predic = np.array(predic)
	acc = metrics.accuracy_score(actual, predic, normalize =  True, sample_weight = None)
	pre = metrics.precision_score(actual, predic, average = 'micro')
	recall = metrics.recall_score(actual, predic, average = 'micro')
	print('Accurancy: {0:5.2f}%'.format(acc * 100))
	print('Precision: {0:5.2f}%'.format(pre * 100))
	print('Recall: {0:5.2f}%'.format(recall * 100))
	plt.show()

def load_n_eval(root, filename, curr_dir, radius = 3):
	test_img, test_label = load_all_img(root, "test")

	os.chdir(curr_dir)
	model = joblib.load(filename)
	eval_model(model, test_label, test_img, radi = radius)


def train_n_eval(root, filename, cur_dir, radius = 3):
	start = time.time()
	train_img, train_label = load_all_img(root, "train")
	train_lbp = compute_lbp(train_img, radi = radius)

	#train model
	model = LinearSVC(random_state = 0, tol = 1e-5)
	model.fit(train_lbp, train_label)
	end = time.time()
	print(f"time taken to the model {end - start}")

	#save model 
	os.chdir(cur_dir)
	joblib.dump(model, filename)

	#eval model
	test_img, test_label = load_all_img(root, "test")
	eval_model(model, test_label, test_img, radi = radius)


# function to display every hist of one image 
# from each catergory
def	compare_lbp_hist(root, mode, radius = 3):
	t = ["Crazing", "Inclusion", "Patches", "Pitted", "Rolled", "Scratches"]
	Inc_img, Inc_name = load_indiv_img(root, mode, t[1], "In_100.bmp")
	Pat_img, Pat_name = load_indiv_img(root, mode, t[2], "Pa_100.bmp")
	Pit_img, Pit_name = load_indiv_img(root, mode, t[3], "PS_100.bmp")
	Craz_img, Craz_name = load_indiv_img(root, mode, t[0], "Cr_100.bmp")
	Rol_img, Rol_name = load_indiv_img(root, mode, t[4], "Rs_100.bmp")
	Scr_img, Scr_name = load_indiv_img(root, mode, t[5], "Sc_100.bmp")

	img = [Inc_img, Pat_img, Pit_img]
	names = [Inc_name, Pat_name, Pit_name]
	analyze_lbp_hist(img, names, radi = radius)
	img = [Craz_img, Rol_img, Scr_img]
	names = [Craz_name, Rol_name, Scr_name]
	analyze_lbp_hist(img, names, radi = radius)

# dataset from
# https://www.kaggle.com/datasets/fantacher/neu-metal-surface-defects-data?resource=download
if __name__ == "__main__":
	filename = 'SVM_modelr3'
	current_dir = os.getcwd()
	# root set to directory of database
	root = r"C:\Users\USER\Desktop\C test\image\NEU Metal Surface Defects Data"
	# radius for lbp , default is 3 if not given
	r = 1

	# used for training and eval the model
	# train_n_eval(root, filename, current_dir)
	# eval trained model
	load_n_eval(root, filename, current_dir)
	# comparing the histogram of different test image
	# compare_lbp_hist(root, "test", r)
