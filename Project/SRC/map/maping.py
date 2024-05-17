import folium
import os

def dmm_to_dd(dmm):
    degrees = int(dmm // 100)
    minutes = dmm - (degrees * 100)
    return degrees + (minutes / 60)
print("\n*Format of degrees and minutes (DMM) has changed to the decimal degrees (DD) format successfully \n")

# Initialize empty list to store locations
locations = []

# Read data from file and store in locations array
with open('file.txt', 'r') as file:
    for line in file:
        lat_str, lon_str = line.strip().split(',')
        lat_dmm = float(lat_str)
        lon_dmm = float(lon_str)
        lat_dd = dmm_to_dd(lat_dmm)
        lon_dd = dmm_to_dd(lon_dmm)
        locations.append([lat_dd, lon_dd])

# Create a map centered at the first point
mymap = folium.Map(location=locations[0], zoom_start=14)

# Add markers for each point
for point in locations:
    folium.Marker(location=point).add_to(mymap)

# Draw a line passing through the given points
folium.PolyLine(locations=locations, color='red').add_to(mymap)

# Specify the path to save the HTML file
html_file_path = 'map_with_line.html'

try:
    # Save the map as an HTML file
    mymap.save(html_file_path)
    print("Map saved successfully as:", os.path.abspath(html_file_path))
except Exception as e:
    print("Error occurred while saving the map:", e)

# Display the map
mymap
