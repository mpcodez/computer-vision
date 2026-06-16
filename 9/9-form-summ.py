import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

pictures = ["circle01a", "circle01b", "circle02", "chatgpt"]

for pic in pictures:
    values = np.loadtxt(f"formative/radius_{pic}.txt")
    
    plt.figure()
    sns.kdeplot(values, fill=True)
    plt.xlabel("Frequency")
    plt.ylabel("Distance")
    plt.xlim(0, 200) 
    plt.title(f"Where is the Radius? For Image {pic}")
    plt.savefig(f"formative/density_{pic}.png", dpi=300)
    plt.close()
