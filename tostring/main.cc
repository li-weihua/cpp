#include <iostream>
#include <string>

int main() {

  int arr[] = {256, 1024, 2048};

  char *arr_char = reinterpret_cast<char *>(arr);

  std::string buffer(arr_char, arr_char + sizeof(int) * 3);

  // buffer to int array
  const int *outarr = reinterpret_cast<const int *>(buffer.data());

  for (int i=0; i<3; ++i) {
    std::cout << outarr[i] << std::endl;
  }

  return 0;
}
