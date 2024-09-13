from console_gfx import display_image, TEST_RAINBOW, load_file

def count_runs(flatData):
    if ":" in flatData:
        return len(flatData)
    count = 1
    for i in range(1,len(flatData)):
        if flatData[i] != flatData[i-1]:
            count+=1
    return count

def to_hex_string(data) -> str:
    hex = ""
    for x in data:
        if (x <= 9):
            hex+=str(x)
        elif x == 10:
            hex+="a"
        elif x == 11:
            hex+="b"
        elif x == 12:
            hex+="c"
        elif x == 13:
            hex+="d"
        elif x == 14:
            hex+="e"
        elif x == 15:
            hex+="f"
    return hex

def encode_rle(flat_data) -> bytes:
    global count
    final = []
    count = 1
    for i in range(1,len(flat_data)):
        if (flat_data[i] != flat_data[i-1]) or (i+1==len(flat_data)):
            final.append(count)
            final.append(flat_data[i-1])
            count = 1
        count+=1
    return bytes(final)

def get_decoded_length(rle_data) -> int:
    amount = 0
    for i in range(0,len(rle_data),2):
        amount+=rle_data[i]
    return amount


def decode_rle(rle_data) -> bytes:
    final = []
    for i in range(0,len(rle_data),2):
        for j in range(0,rle_data[i]):
            final.append(rle_data[i+1])
    return bytes(final)


def string_to_data(data_string: str) -> bytes:
    final = []
    keys = {"0":0,"1":1,"2":2,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9,"a":10,"b":11,"c":12,"d":13,"e":14,"f":15}
    for i in range(0,len(data_string)):
        final.append(keys[data_string[i]])
    return bytes(final)

def to_rle_string(rleData) -> str:
    final = ""
    keys = {0:"0",1:"1",2:"2",3:"3",4:"4",5:"5",6:"6",7:"7",8:"8",9:"9",10:"a",11:"b",12:"c",13:"d",14:"e",15:"f"}
    for i in range(0,len(rleData)-1):
        final += keys[rleData[i]]+keys[rleData[i+1]]+":"
    return final




print(to_rle_string([10,15,6,4]))
def main():
    global file, going
    going = True
    file = "image_files/gator.gfx"
    print("Welcome to the RLE image encoder!")
    print("\nDisplaying Spectrum Image:")
    display_image(TEST_RAINBOW)
    while going:
        print("\n RLE Menu")
        print("------------")
        print("0. Exit")
        print("1. Load File")
        print("2. Load Test Image")
        print("3. Read RLE String")
        print("4. Read RLE Hex String")
        print("5. Read Data Hex String")
        print("6. Display Image")
        print("7. Display RLE Image")
        print("8. Display Hex RLE Data")
        print("9. Display Hex Flat Data")
        option = int(input("Select a Menu Option: "))
        if option == 1:
            file = input("Enter name of file to load: ")
        elif option == 2:
            print("Test image data loaded.")
            file = load_file(file)
        elif option == 6:
            display_image(file.hex())

