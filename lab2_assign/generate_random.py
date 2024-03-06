import random

def generate_input(num_processes):
    inputs = []
    for _ in range(num_processes):
        arrival_time = random.randint(0, 100)
        total_cpu_time = random.randint(100, 500)
        cpu_burst = random.randint(10, 100)
        io_burst = random.randint(10, 100)
        inputs.append(f"{arrival_time:03d} {total_cpu_time:03d} {cpu_burst:03d} {io_burst:03d}\n")
    return inputs

def write_to_file(inputs, file_index):
    filename = f"input{file_index}"
    with open(filename, 'w') as f:
        f.writelines(inputs)

def generate_and_write(num_files, num_processes_per_file):
    for i in range(num_files):
        inputs = generate_input(num_processes_per_file)
        write_to_file(inputs, i + 9)

if __name__ == "__main__":
    num_files = 500
    num_processes_per_file = 20
    generate_and_write(num_files, num_processes_per_file)
    print(f"{num_files} files generated.")
