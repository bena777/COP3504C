from console_gfx import display_image, TEST_RAINBOW, load_file, TEST_IMAGE

def count_runs(flatData): # counts the amount of runs in dataset
    global current_var,current_count
    count = 1
    current_count = 0
    for i in range(1,len(flatData)): #iterates by count so that if current is dif than prev, it adds a count since its a new run
        if (flatData[i] != flatData[i-1]) or (current_count == 15):
            count+=1
            current_count = 0
        else:
            current_count+=1
    return count

def to_hex_string(data) -> str: # converts flat data to hex by using string formatting and .join() function to rid unnecessary spaces
    hex = [f"{x:x} " for x in data]
    return ''.join(hex).replace(" ",'')
def encode_rle(flat_data) -> bytes:
    final = []
    count = 1
    for i in range(1, len(flat_data)):
        if flat_data[i] == flat_data[i - 1]: # adds additional count to current run if prev is same as current
            count += 1
        else:
            while count > 0: # takes minimum between count and limit (15) and appends that to final as well sa the actual character
                run_length = min(count, 15)
                final.append(run_length)
                final.append(flat_data[i - 1])
                count -= run_length # subtracts the current run length from count to eventually end loop
            count = 1
    while count > 0: # deals with final run in data
        run_length = min(count, 15)
        final.append(run_length)
        final.append(flat_data[-1])
        count -= run_length
    return bytes(final)


def get_decoded_length(rle_data) -> int:
    amount = 0
    if isinstance(rle_data, bytes): # checks for if the data is a byte type and if it is, turns it into list
        rle_data = list(rle_data)
    for i in range(0, len(rle_data), 2): # goes to every even index of data and
        amount += rle_data[i]
    return amount


def decode_rle(rle_data) -> bytes:
    final = []
    rle_data = list(rle_data)
    for x in range(0,len(list(rle_data)),2):
        if rle_data[x] > 15:
            rle_data[x] = 15
    for i in range(0,len(rle_data),2): # checks every even index of rle_data (run length) and for the number of times "n" this is it appends the value n times to the final list
        for j in range(0,rle_data[i]):
            final.append(rle_data[i+1])
    return bytes(final)


def string_to_data(data_string: str) -> bytes:
    final = []
    keys = {"0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15,"a":10,"b":11,"c":12,"d":13,"e":14,"f":15}
    for i in range(0, len(data_string)): # iterates through every char in data string and appends the key of that to the final list
        final.append(keys[data_string[i]])
    return bytes(final) # converts list to bytes

def to_rle_string(rleData) -> str:
    final = ""
    keys = {0:"0",1:"1",2:"2",3:"3",4:"4",5:"5",6:"6",7:"7",8:"8",9:"9",10:"a",11:"b",12:"c",13:"d",14:"e",15:"f"}
    for i in range(0,len(rleData),2): # iterates through every even index of rleData and adds it plus its corosponding odd index plus a semi colon for formatting
        final += str(rleData[i])+keys[rleData[i+1]]+":"
    return final[:-1]


def string_to_rle(rleString: str) -> bytes:
    finals = []
    segments = rleString.split(':')
    for segment in segments:
        if len(segment) > 1: # loops through every segment in formatted string split by semi colons
            length_str = segment[:-1]
            value_str = segment[-1]
            length = int(length_str, 16) # converts length and value strs into base 16 (hex)
            value = int(value_str, 16)
            finals.append(length)
            finals.append(value)
    return bytes(finals)




def main():
    global going, image_data
    going = True
    image_data = None
    print("Welcome to the RLE image encoder!")
    print("\nDisplaying Spectrum Image: ")
    print("")
    print("")
    display_image(TEST_RAINBOW)
    while going:
        print("\nRLE Menu")
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
                image_data = load_file(input("Enter name of file to load: ")) #loads file
            except:
                print("Image location not found!")
        elif option == "2":
            print("Test image data loaded.") # loads test image
            image_data = TEST_IMAGE
        elif option == "3":
            decode = input("Enter an RLE string to be decoded: ") # decodes rle
            image_data = string_to_rle(decode)
        elif option == "4":
            decode = input("Enter the hex string holding RLE data: ")
            image_data = decode
            print("RLE decoded length: "+str(get_decoded_length(image_data))) # prints decoded run length of hex str
        elif option == "5":
            image_data = string_to_data(input("Enter the hex string holding flat data: ")) # converts hex str to
            print("Number of runs: "+str(count_runs(image_data)))
        elif option == "6":
            print("Displaying image...")
            if not image_data:
                print("(no data)")
            else:
                try:
                    display_image(image_data) # in case of bytes
                except:
                    if ":" in list(image_data): # in case of formatted str
                        display_image(decode_rle(string_to_rle(image_data)))
                    else: # in case of list or elsewise
                        display_image(decode_rle(string_to_data(image_data)))
        elif option == "7":
            if not image_data:
                print("RLE representation: (no data)")
            else:
                print("RLE representation: "+to_rle_string(encode_rle(image_data))) # displays encoded rle string
        elif option == "8":
            if not image_data:
                print("RLE hex values: (no data)")
            else:
                print("RLE hex values: "+to_hex_string(encode_rle(image_data))) # displays encoded hex string
        elif option == "9":
            if not image_data:
                print("Flat hex values: (no data)")
            else:
                print("Flat hex values: "+ to_hex_string(decode_rle(image_data))) # displays regular hex fvalues
        elif option == "0": # stops program
            break
        else:
            print("Error! Invalid input.")

if __name__ == "__main__":
    main()
