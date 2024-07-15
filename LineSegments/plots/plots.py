import matplotlib.pyplot as plt

def plot_line_graph(file_paths):
    colors = ['r','b']  # Blue for the first file, Red for the second file
    j = int(file_paths[1][7])

    for i, file_path in enumerate(file_paths):
        x = []
        y = []

        with open(file_path, 'r') as file:
            for line in file:
                data = line.strip().split()
                x.append(float(data[0]))
                y.append(float(data[1]))

        plt.plot(x, y, color=colors[i], label=f'File {j}')

        plt.xlabel('X-axis Label')
        plt.ylabel('Y-axis Label')
        plt.title(f'Line Graph - {file_path}')
        plt.grid(True)
        plt.legend()
        plt.savefig(f"plot_{j}.png")
    plt.clf()

# Example usage:
file_paths = [
              ['my_outline1.txt','outline1'],
              ['my_outline2.txt','outline2'],
              ['my_outline3.txt','outline3'],
              ['my_outline4.txt','outline4'],
              ['my_outline5.txt','outline5'],
              ['my_outline6.txt','outline6'],
              ['my_outline7.txt','outline7'],
              ['my_outline8.txt','outline8'],
              ['my_outline9.txt','outline9'],
              ['my_outline10.txt','outline10'],
              ] # Update with the paths to your text files
for i in file_paths:
    plot_line_graph(i)
