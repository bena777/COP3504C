from console_gfx import display_image, TEST_RAINBOW, load_file, TEST_IMAGE
import re

def count_runs(flatData):
    count = 1
    for i in range(1,len(flatData)):
        if flatData[i] != flatData[i-1]:
            count+=1
    return count

def to_hex_string(data) -> str:
    hex = [f"{x:x} " for x in data]
    return ''.join(hex).replace(" ",'')


def encode_rle(flat_data) -> bytes:
    global count
    final = []
    count = 1
    keys2 = {"0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "a": 10, "b": 11, "c": 12, "d": 13, "e": 14, "f": 15}
    for i in range(1,len(flat_data)):
        if (flat_data[i] != flat_data[i-1]) or (i+1==len(flat_data)):
            if count > 15:
                count = 15
            final.append(count)
            final.append(keys2[flat_data[i-1]])
            count = 1
        count+=1
    return bytes(final)

def get_decoded_length(rle_data) -> int:
    amount = 0
    keys = {"0":0,"1":1,"2":2,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9,"A":10,"B":11,"C":12,"D":13,"E":14,"F":15}
    for i in range(0,len(rle_data),2):
        amount+=keys[rle_data[i]]
    return amount


def decode_rle(rle_data) -> bytes:
    final = []
    for i in range(0,len(rle_data),2):
        for j in range(0,rle_data[i]):
            final.append(rle_data[i+1])
    return bytes(final)


def string_to_data(data_string: str) -> bytes:
    final = []
    keys = {"0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "a": 10, "b": 11, "c": 12, "d": 13, "e": 14, "f": 15}
    for i in range(0, len(data_string)):
        final.append(keys[data_string[i]])
    return bytes(final)

def to_rle_string(rleData) -> str:
    final = ""
    print(rleData)
    keys = {0:"0",1:"1",2:"2",3:"3",4:"4",5:"5",6:"6",7:"7",8:"8",9:"9",10:"a",11:"b",12:"c",13:"d",14:"e",15:"f"}
    for i in range(0,len(rleData),2):
        final += str(rleData[i])+keys[rleData[i+1]]+":"
    return final


def string_to_rle(rleString: str) -> bytes:
    finals = []
    segments = rleString.split(':')
    for segment in segments:
        if len(segment) > 1:
            length_str = segment[:-1]
            value_str = segment[-1]
            length = int(length_str, 16)
            value = int(value_str, 16)
            finals.append(length)
            finals.append(value)
    return bytes(finals)




def main():
    global going, image_data
    going = True
    image_data = None
    print("Welcome to the RLE image encoder!")
    print("\nDisplaying Spectrum Image:")
    display_image(TEST_RAINBOW)
    while going:
        print("\n RLE Menu")
        print("--------")
        print("0. Exit")
        print("1. Load File")
        print("2. Load Test Image")
        print("3. Read RLE String")
        print("4. Read RLE Hex String")
        print("5. Read Data Hex String")
        print("6. Display Image")
        print("7. Display RLE String")
        print("8. Display Hex RLE Data")
        print("9. Display Hex Flat Data")
        option = input("Select a Menu Option: ")
        if option == "1":
            try:
                image_data = load_file(input("Enter name of file to load: "))
            except:
                print("Image location not found!")
        elif option == "2":
            print("Test image data loaded.")
            image_data = TEST_IMAGE
        elif option == "3":
            decode = input("Enter an RLE string to be decoded: ")
            image_data = string_to_rle(decode)
        elif option == "4":
            decode = input("Enter the hex string holding RLE data: ")
            image_data = decode_rle(decode)
            print("RLE decoded length: "+str(get_decoded_length(image_data)))
        elif option == "5":
            image_data = input("Enter the hex string holding flat data: ")
            print("Number of runs: "+str(count_runs(image_data)))
        elif option == "6":
            print("Displaying image...")
            if not image_data:
                print("(no data)")
            else:
                display_image(image_data)
        elif option == "7":
            if not image_data:
                print("RLE representation: (no data)")
            else:
                print("RLE representation: "+to_rle_string(image_data))
        elif option == "8":
            if not image_data:
                print("RLE hex values: (no data)")
            else:
                print("RLE hex values: "+str(to_hex_string(encode_rle(to_hex_string(image_data)))))
        elif option == "9":
            if not image_data:
                print("Flat hex values: (no data)")
            else:
                print("Flat hex values: "+ to_hex_string(image_data))
        else:
            print("Error! Invalid input.")

if __name__ == "__main__":
    main()
