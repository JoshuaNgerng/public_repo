import pandas as pd
import numpy as np
from tabulate import tabulate
import skfuzzy as fuz
import matplotlib.pyplot as plt 
import tkinter as tk
from PIL import Image, ImageTk

# generate global axes for function
def get_list_xset():
	x_ws = np.arange(6, 10, 0.05)
	x_cws = np.arange(-2, 2, 0.05)
	x_cf = np.arange(-0.2, 0.2, 0.005)
	x_out = np.arange(0, 1, 0.005)
	output = [x_ws, x_cws, x_cf, x_out]
	return (output)

def get_fuzzyset(xset):
	ws_NB = fuz.trimf(xset[0], [6, 6, 6.7])
	ws_NM = fuz.trimf(xset[0], [6, 6.7, 7.3])
	ws_NS = fuz.trimf(xset[0], [6.7, 7.3, 8])
	ws_ZO = fuz.trimf(xset[0], [7.3, 8, 8.7])
	ws_PS = fuz.trimf(xset[0], [8, 8.7, 9.3])
	ws_PM = fuz.trimf(xset[0], [8.7, 9.3, 10])
	ws_PB = fuz.trimf(xset[0], [9.3, 10, 10])
	ws_set = [ws_NB, ws_NM, ws_NS, ws_ZO, ws_PS, ws_PM, ws_PB]
	cws_NB = fuz.trimf(xset[1], [-2, -2, -1.3])
	cws_NM = fuz.trimf(xset[1], [-2, -1.3, -0.7])
	cws_NS = fuz.trimf(xset[1], [-1.3, -0.7, 0])
	cws_ZO = fuz.trimf(xset[1], [-0.7, 0, 0.7])
	cws_PS = fuz.trimf(xset[1], [0, 0.7, 1.3])
	cws_PM = fuz.trimf(xset[1], [0.7, 1.3, 2])
	cws_PB = fuz.trimf(xset[1], [1.3, 2, 2])
	cws_set = [cws_NB, cws_NM, cws_NS, cws_ZO, cws_PS, cws_PM, cws_PB]
	cf_NB = fuz.trimf(xset[2], [-0.2, -0.2, -0.13])
	cf_NM = fuz.trimf(xset[2], [-0.2, -0.13, -0.07])
	cf_NS = fuz.trimf(xset[2], [-0.13, -0.07, 0])
	cf_ZO = fuz.trimf(xset[2], [-0.07, 0, 0.07])
	cf_PS = fuz.trimf(xset[2], [0, 0.07, 0.13])
	cf_PM = fuz.trimf(xset[2], [0.07, 0.13, 0.2])
	cf_PB = fuz.trimf(xset[2], [0.13, 0.2, 0.2])
	cf_set = [cf_NB, cf_NM, cf_NS, cf_ZO, cf_PS, cf_PM, cf_PB]
	out_NB = fuz.trimf(xset[3], [0, 0, 0.17])
	out_NM = fuz.trimf(xset[3], [0, 0.17, 0.33])
	out_NS = fuz.trimf(xset[3], [0.17, 0.33, 0.5])
	out_ZO = fuz.trimf(xset[3], [0.33, 0.5, 0.67])
	out_PS = fuz.trimf(xset[3], [0.5, 0.67, 0.83])
	out_PM = fuz.trimf(xset[3], [0.67, 0.83, 1])
	out_PB = fuz.trimf(xset[3], [0.83, 1, 1])
	out_set = [out_NB, out_NM, out_NS, out_ZO, out_PS, out_PM, out_PB]
	output = [ws_set, cws_set, cf_set, out_set]
	return (output)

# visualation memebership function
def graph_fuzzy_set(xset, fset):
	fig, (ax0, ax1, ax2, ax3) = plt.subplots(nrows=4, figsize=(8, 9))
	name = ["Wind speed", "Change in Wind Speed", "Change in Frequency", "Output"]
	colour = ['b', 'g', 'r', 'm', 'b', 'g', 'r']
	label = ["NB", "NM", "NS", "ZO", "PS", "PM", "PB"]

	i = 0
	for ax in (ax0, ax1, ax2, ax3):
		for j in range(7):
			ax.plot(xset[i], fset[i][j], colour[j], linewidth = 1.5, label = label[j])
		ax.set_title(name[i])
		ax.spines['top'].set_visible(False)
		ax.spines['right'].set_visible(False)
		ax.get_xaxis().tick_bottom()
		ax.get_yaxis().tick_left()
		i += 1
	ax0.legend(loc = "lower right")

	plt.tight_layout()
	plt.show()

def truth_table7(i, j):
	col1 = ['NS', 'ZO', 'ZO', 'PM', 'PB', 'PB', 'PB']
	col2 = ['NS', 'NS', 'ZO', 'PS', 'PM', 'PB', 'PB']
	col3 = ['NM', 'NS', 'NS', 'ZO', 'PM', 'PM', 'PB']
	col4 = ['NM', 'NM', 'NS', 'ZO', 'PS', 'PM', 'PM']
	col5 = ['NB', 'NM', 'NM', 'ZO', 'PS', 'PB', 'PM']
	col6 = ['NB', 'NB', 'NM', 'NS', 'ZO', 'PB', 'PS']
	col7 = ['NB', 'NB', 'NB', 'NM', 'ZO', 'ZO', 'PS']
	table = [col1, col2, col3, col4, col5, col6, col7]
	return (table[i][j])

def fuzzy_rules7(mem_list, fset, var):
	aggreate = []
	for i in range(7):
		buffer_list = []
		for j in range(7):
			consquent = truth_table7(i, j)
			rule = np.fmax(mem_list[var][j], mem_list[2][i])
			if (consquent == 'NB'):
				buffer = np.fmin(rule, fset[0])
			if (consquent == 'NM'):
				buffer = np.fmin(rule, fset[1])
			if (consquent == 'NS'):
				buffer = np.fmin(rule, fset[2])
			if (consquent == 'ZO'):
				buffer = np.fmin(rule, fset[3])
			if (consquent == 'PS'):
				buffer = np.fmin(rule, fset[4])
			if (consquent == 'PM'):
				buffer = np.fmin(rule, fset[5])
			if (consquent == 'PB'):
				buffer = np.fmin(rule, fset[6])
			buffer_list.append(buffer)
		aggreate.append(buffer_list)
	return(aggreate)

# fuzzy rules1
def process_fuzzy_rules7(input, xset, fset):
	mem_list = []
	for i in range(3):
		buffer = []
		for j in range(7):
			mem = fuz.interp_membership(xset[i], fset[i][j], input[i])
			buffer.append(mem)
		mem_list.append(buffer)

	aggreate_f1 = fuzzy_rules7(mem_list, fset[3], 0)
	aggreate_f2 = fuzzy_rules7(mem_list, fset[3], 1)
	return (aggreate_f1, aggreate_f2)

def total_agg(eval1, eval2):
	for i in range(7):
		agg1 = np.fmax(eval1[i][0], eval1[i][1])
		agg2 = np.fmax(eval2[i][0], eval2[i][1])
		for j in range(5):
			agg1 = np.fmax(eval1[i][j + 2], agg1)
			agg2 = np.fmax(eval2[i][j + 2], agg2)
	return(np.fmax(agg1, agg2))

def defuzzfication(x_out, total):
	output = []
	methods = ['centroid', 'bisector', 'mom', 'som', 'lom']
	for i in range(5):
		buffer = fuz.defuzz(x_out, total, methods[i])
		output.append(buffer)
	return(output)
	

def graph_defuzzy(x_out, fset, agg, xvals):
	names = ['centroid', 'bisector', 'mean of maximum', 
			'min of maximum', 'max of maximum']
	colour_graph = ['b', 'g', 'r', 'm', 'b', 'g', 'r']
	colour_output = ['r', 'b', 'g', 'c', 'm']
	ymax = []
	for i in range(5):
		buffer = fuz.interp_membership(x_out, agg, xvals[i])
		ymax.append(buffer)
	x_0 = np.zeros_like(x_out)

	fig, ax = plt.subplots(figsize=(8, 3))
	for i in range(7):
		ax.plot(x_out, fset[i], colour_graph[i], linewidth=0.5, linestyle='--', )
	ax.fill_between(x_out, x_0, agg, facecolor = 'Orange', alpha=0.7)
	for j in range(5):
		ax.vlines(xvals[j], 0, ymax[j], label = names[j], color = colour_output[j])
	ax.set_title('Aggregated membership and result (line)')
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.get_xaxis().tick_bottom()
	ax.get_yaxis().tick_left()

	plt.tight_layout()
	plt.show()

def do_fuzz(x, xset, fset):
	foutput1, foutput2 = process_fuzzy_rules7(x, xset, fset)
	total = total_agg(foutput1, foutput2)
	return(defuzzfication(xset[3], total))


def eval(input1, input2, input3, xset):
	fset = get_fuzzyset(xset)
	try:
		num = 0
		for i in range(len(input1)):
			for j in range(len(input2)):
				for k in range(len(input3)):
					x = [input1[i], input2[j], input3[k]]
					do_fuzz(x, xset, fset)
					num += 1
		print(f"there is {num} number of fuzzy processes")
	except:
		print('Error')
		print(f"at i = {i}, j = {j}, k = {k} with values {input1[i]}, {input2[j]}, {input3[k]}")

def get_table_compare(test_in, xset):
	fset = get_fuzzyset(xset)
	in_arr = []
	cout = []
	bout = []
	meanout = []
	minout = []
	maxout = []
	for i in range(5):
		in_arr.append(test_in[i])
		output = do_fuzz(test_in[i], xset, fset)
		cout.append(output[0])
		bout.append(output[1])
		meanout.append(output[2])
		minout.append(output[3])
		maxout.append(output[4])
	data = {"Input": in_arr, "Centroid": cout, "Bisector": bout, 
	 		"Mean of maximum": meanout, "Min of maximum": minout, "Max of maximum": maxout}
	df = pd.DataFrame(data)
	print(tabulate(df, headers='keys', tablefmt='fancy_grid'))

def get_table_eval(test_in, xset):
	fset = get_fuzzyset(xset)
	ws =[]
	cws = []
	cf = []
	out = []
	for i in range(13):
		ws.append(test_in[i][0])
		cws.append(test_in[i][1])
		cf.append(test_in[i][2])
		print(i)
		output = do_fuzz(test_in[i], xset, fset)
		out.append(output[0])
	data = {"Wind speed": ws, "Change in Wind Speed": cws, 
	 		"Change in Frequency": cf, "Output": out}
	df = pd.DataFrame(data)
	print(tabulate(df, headers='keys', tablefmt='fancy_grid'))

# table1
def get_compare_table():
	p1 = [6, -2, -0.5]
	p2 = [6, 2, -0.5]
	p3 = [8, -1, 0.5]
	p4 = [10, 0, 0]
	p5 = [7, -1.5, 1]
	test_input = [p1, p2, p3, p4, p5]
	get_table_compare(test_input, xset)

# table2
def get_eval_table():
	p1 = [6, -2, -0.1]
	p2 = [6, 0, -0.1]
	p3 = [6, 2, -0.1]
	p4 = [9, 2, -0.1]
	p5 = [8, 2, -0.1]
	p6 = [9, 1, -0.1]
	p7 = [7, -2, -0.1]
	p8 = [8, -2, -0.1]
	p9 = [10, -2, -0.1]
	p10 = [6, 0, 0]
	p11 = [6, 0, 0.1]
	p12 = [6, 0, 0.2]
	p13 = [6, 0, -0.2]
	test_input = [p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13]
	get_table_eval(test_input, xset)

def get_input(val1, val2, val3):
	ws = float(val1.get())
	cws = float(val2.get())
	cf = float(val3.get()) / 10
	return ([ws, cws, cf])

if __name__ == '__main__':
	#global constant for the GUI
	xset = get_list_xset()
	fset = get_fuzzyset(xset)

	#set up GUI
	root = tk.Tk()
	root.title('Example')
	sliderVal1 = tk.DoubleVar()
	sliderVal2 = tk.DoubleVar()
	sliderVal3 = tk.DoubleVar()

	# slide for wind speed
	left_icon = Image.open('.\light.jpg').resize((100, 100))
	right_icon = Image.open('.\gust.jpg').resize((100, 100))
	left_icon_tk = ImageTk.PhotoImage(left_icon)
	right_icon_tk = ImageTk.PhotoImage(right_icon)
	label = tk.Label(root, text = 'Wind Speed: 6 m/s', font = ('Arial', 15))
	label.grid(row = 1, column = 1, pady = 2)
	slider_label_left = tk.Label(root, image = left_icon_tk, text = 'Light breeze', compound = 'left')
	slider_label_left.grid(row = 2, column = 0, pady = 2)
	slider = tk.Scale(root, from_ = 6, to = 10, orient = 'horizontal', length = 200, variable = sliderVal1, 
		   			  command=lambda value: label.config(text=f'Wind Speed: {value} m/s'))
	slider.grid(row = 2, column = 1, pady = 2)
	slider_label_right = tk.Label(root, image = right_icon_tk, text = 'Gust', compound = 'right')
	slider_label_right.grid(row = 2, column = 2, pady = 2)

	# slide for change in wind speed
	label2 = tk.Label(root, text= 'Change in Wind Speed: 0 m/s^-2')
	label2.grid(row = 3, column = 1, pady = 2)
	slider_label_left2 = tk.Label(root, text = 'Slowing down', compound='left')
	slider_label_left2.grid(row = 4, column = 0, pady = 2)
	slider2 = tk.Scale(root, from_ = -2, to = 2, orient='horizontal', length=200, 
		    		   command=lambda value: label2.config(text=f'Change in Wind Speed: {value} m/s^-2'))
	slider2.grid(row = 4, column = 1, pady = 2)
	slider_label_right2 = tk.Label(root, text = 'Accelerating', compound = 'right')
	slider_label_right2.grid(row = 4, column = 2, pady = 2)

	# slide for change in frequency
	label3 = tk.Label(root, text= 'Change in Frequency: 0 Hz')
	label3.grid(row = 5, column = 1, pady = 2)
	slider_label_left3 = tk.Label(root, text = 'Increase in Load demand', compound = 'left')
	slider_label_left3.grid(row = 6, column = 0, pady = 2)
	slider3 = tk.Scale(root, from_ = -2, to = 2, orient='horizontal', length=200, 
		    			command=lambda value: label3.config(text = f'Change in Frequency: {value} X 10 ^-1 Hz'))
	slider3.grid(row=6, column = 1, pady = 2)
	slider_label_right3 = tk.Label(root, text = 'Decrease in Load demand', compound = 'right')
	slider_label_right3.grid(row = 6, column = 2, pady = 2)

	output_icon = Image.open('.\house.JPG').resize((60,60))
	output_icon_tk = ImageTk.PhotoImage(output_icon)
	output_icon_label = tk.Label(root, image = output_icon_tk,compound = 'left')
	output_label = tk.Label(root, text = "Percentage Energy Supplied to Household: ")
	
	
	def compute():
		x = get_input(sliderVal1, sliderVal2, sliderVal3)
		out = do_fuzz(x, xset, fset)
		output_icon_label.grid(row = 8, column = 5, pady = 2, padx = (300,2))
		output_label.grid(row = 8, column = 5, padx = (0,50))
		output_label.config(text = f'Percentage Energy Supplied: {round(out[0] * 100, 1)}%')

	cal_button = tk.Button(root, text= "Calculate", 
							command = compute)
	cal_button.grid(row = 14, column = 1, padx = 40)
	root.mainloop()

# evaluating the system across many inputs
# eval(np.arange(6, 10, 0.1), np.arange(-2, 2, 0.1), 
#    np.arange(-0.2, 0.2, 0.05), get_list_xset())