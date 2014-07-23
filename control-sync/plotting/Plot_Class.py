########## Import proper Libraries ##########
import csv
import numpy
import operator
import datetime
import itertools
import matplotlib.pyplot as plt

########## Plotting Class using Matplotlib ##########
class Plotting(object):

	### Initialize objects ###
	def __init__(self):
		self.datafile = ''	# Name of data file
		self.dataorganized = ''	# Holds gathered data
		self.ChosenData = []	# Holds data for specific field
		self.ConvertedTime = []	# Holds converted datetime objects
		self.BeginDate = 0	# Begin date for data plotted
		self.EndDate = 0	# End date for data plotted
		self.BeginIndex = 0	# Begin index of data plotted
		self.EndIndex = 0	# End index of data plotted
		self.x = []		# Time data for x-axis
		self.y = []		# Field data for y-axis
		self.color = 'b'	# Color of data for specific field
		self.colors = itertools.cycle(['r','g','y','c','m','k','b'])
		self.legend_titles = []	# Titles of plotted data for legend


	### Choose and open Data File ###
	def choose_file(self, filename):

		# Open data file
		self.datafile = open(filename, 'r')


	### Input time interval ###
	# Using begin and end date, finds time data for x-axis of graph
	def input_time(self, BeginDateIn, EndDateIn):

		# Gather the Data
		self.dataorganized = csv.DictReader(self.datafile)

		# Convert input dates
		self.BeginDate = datetime.datetime.strptime(BeginDateIn + "00", "%Y-%m-%d %H:%M:%S.%f%z")
		self.EndDate = datetime.datetime.strptime(EndDateIn + "00", "%Y-%m-%d %H:%M:%S.%f%z")

		# Convert time
		self.ConvertedTime = self.convert_date(self.dataorganized)

		# Find index for time
		self.BeginIndex = self.find_index(self.BeginDate, self.ConvertedTime)
		self.EndIndex = self.find_index(self.EndDate, self.ConvertedTime)

		# Obtain the dates for plotting
		self.x = self.gather_dates(self.ConvertedTime, self.BeginIndex, self.EndIndex)


	### Input data field to plot ###
	# Finds data over a time range for a certain field to plot on the y-axis
	def input_field(self, field):

		# Add field to legend titles
		self.legend_titles.append(field)

		# Get chosen data
		self.dataorganized = csv.DictReader(self.datafile)
		self.datafile.seek(0) #Reset iterator
		self.ChosenData = self.get_data(self.dataorganized, field)

		# Obtain the chosen data in the specified range
		self.y = self.gather_chosen(self.ChosenData, self.BeginIndex, self.EndIndex)


	### Convert Data String  -> Float ###
	# Converts data in a specified field to a float
	def convert_to_float(self, row, field):

		# Check if there is data
		if(row[field] == ''):
			# No data is not a number
			row[field] = float('nan')
			return row[field]

		else:
			# Convert value and return
			row[field] = float(row[field])
			return row[field]


	### Pull out the non-date data ###
	# Extracts the data from a specified field (not time)
	def get_data(self, data, field):

		# Establish a Variable
		value = []

		# Loop through the data
		for row in data:
		
			# Store the seeked data
			value.append(self.convert_to_float(row, field))

		# Return the desired data
		return value


	### Convert the date String -> Datetime ###
	# Converts the date string into a Datetime object
	def convert_date(self, data):
	
		# Establish a Variable
		t = []
		field = "db_time"

		# Loop through the data
		for row in data:	

			# Store the date
			t.append(datetime.datetime.strptime(row[field]+"00", "%Y-%m-%d %H:%M:%S.%f%z"))

		# Return
		return t


	### Find the index of data ###
	# Using input date, return index
	def find_index(self, InputDate, ConvertedSet):

		# Establish a variable
		index = 0

		# Begin looping
		for row in ConvertedSet:
		
			# Check for a match
			if(InputDate.year == row.year):
				if(InputDate.month == row.month):
					if(InputDate.day == row.day):
						if(InputDate.hour == row.hour):
							if(InputDate.minute == row.minute):
								if(InputDate.second == row.second):
									return index
								else:
									index += 1
							else:
								index += 1
						else:
							index += 1
					else:
						index += 1
				else:
					index += 1
			else:
				index += 1


	### Gather the chosen data in the range ###
	# Using the beginning index and end index, returns chosen data in range
	def gather_chosen(self, ChosenData, BeginIndex, EndIndex):
	
		# Establish a storing variable
		chosen = []

		# Establish a while Loop
		while(BeginIndex >= EndIndex):
	
			# Begin gathering
			chosen.append(ChosenData[BeginIndex])

			# Decrement
			BeginIndex -= 1

		# Return the data
		return chosen


	### Gather the Dates for plotting ###
	# Using the beginning index and end index, returns range of dates
	def gather_dates(self, ConvertedTime, BeginIndex, EndIndex):
	
		# Establish variables
		range = []
	
		# Establish while loop
		while(BeginIndex >= EndIndex):
		
			# Gather the dates
			range.append(ConvertedTime[BeginIndex])

			# Decrement
			BeginIndex -= 1
	
		# Return the dates
		return range


	### Plot Data ###
	# Plots the data as a scatter plot using times and data and formats plot
	def plot_data(self):

		# Plot data as a scatter plot
		plt.scatter(self.x, self.y, c = self.color, marker='.', edgecolors='none')

		# Plot Format
		plt.xlabel('Time')
		plt.title('Weather Box Data')
		plt.xlim(self.BeginDate, self.EndDate)
		plt.legend(self.legend_titles, loc='best', scatterpoints=1, fontsize=8)

		# Change color for next plot
		self.color = next(self.colors)


	### Save plot ###
	# Saves the plot as a .png and displays plot
	def save_plot(self):

		# Save plot as .png
		plt.savefig('WeatherboxData_Graph.png')

		# Display plot
		plt.show()


########## Main ##########
# Establish variable to indicate whether or not to plot more
PlotMore = True

# Create class
weatherbox = Plotting()

# Ask for file name of data user would like to plot and choose file
filename = input('Enter file name: ')
weatherbox.choose_file(filename)

# Ask user for beginning and end date and field
BeginDateIn = input('Enter beginning date and time(Y-m-d H:M:S.mS-GMT): ')
EndDateIn = input('Enter end date and time(Y-m-d H:M:S.mS-GMT): ')
field = input('Enter data field: ')
print('Please wait...')

# Get x-axis time data
weatherbox.input_time(BeginDateIn, EndDateIn)

while(PlotMore):

	# Get field data for y-axis
	weatherbox.input_field(field)

	# Plot the data
	weatherbox.plot_data()

	# Ask user if they would like to plot more data
	response = input('Would you like to plot more data (Y or N)?: ')

	# Check response
	if(response == "Y" or response == "y" or response == "Yes"):

		# Ask for data field and get field data for y-axis
		field = input('Enter data field: ')
		weatherbox.input_field(field)

		# Still plotting more data
		PlotMore = True

	elif(response == "N" or response == "n" or response == "No"):

		# End the loop
		PlotMore = False

	else:
		
		# Error
		print('Invalid Response')

# Save plot as .png and display
weatherbox.save_plot()

# Close file
weatherbox.datafile.close()
