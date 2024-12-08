import csv

# gerei esse codigo do chatgpt

# Function to read the CSV file and create a list of tuples
def create_tuples_from_csv(filename):
    tuples_list = []
    
    # Open the CSV file in read mode
    with open(filename, mode='r') as file:
        # Create a CSV reader object
        csv_reader = csv.reader(file)
        
        # Loop through each row in the CSV file
        for row in csv_reader:
            # Convert the row into a tuple and append to the list
            # Convert each item to the appropriate type (float or int)
            row_tuple = tuple(map(float, row))
            tuples_list.append(row_tuple)
    
    return tuples_list

# Example usage:

filenames = [("astar8","data/astar8_data.csv"),("astar15","data/astar15_data.csv"),("bfs","data/bfs_data.csv"),("idastar","data/idastar_data.csv"),("gbfs","data/gbfs_data.csv"),("idfs","data/idfs_data.csv")]
dicionario ={}
for filename in filenames:
    tuples = create_tuples_from_csv(filename[1])
    dicionario[filename[0]] = tuples
for key in dicionario:
    print(key)
    print(dicionario[key])


# Print the resulting list of tuples
