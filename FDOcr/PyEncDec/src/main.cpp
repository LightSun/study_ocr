#include "pybind11/numpy.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eval.h>

#include <type_traits>
#include "AES.h"
#include "../com/com.h"

namespace h7 {

namespace py = pybind11;
using namespace py::literals;

using String = std::string;
using CString = const std::string&;

//*指针-->numpy 1D
template<typename T>
py::array_t<T> _ptr_to_arrays_1d(const T* data, py::ssize_t col) {
    auto result = py::array_t<T>(col);//申请空间
    py::buffer_info buf = result.request();
    T* ptr = (T*)buf.ptr;

    for (auto i = 0; i < col; i++)
        ptr[i] = data[i];

    return result;
}

class PyEncDec{
public:
    py::array_t<char> decFile(CString inFile){
        String key1 = "@(**^$$%&)((&^^(";
        String key2 = "8g77d7fg7&%%(*^^";
        auto cs = EncDecPy::getFileContent0(inFile);
        if(cs.empty()){
            fprintf(stderr, "open input failed: %s\n", inFile.data());
            return {};
        }
        {
            med_ed::AES aes(8, 2 << 20);
            auto decCs = aes.cfb128(cs, key1, key2, false);
            if(decCs.empty()){
                fprintf(stderr, "dec failed, file = %s\n", inFile.data());
            }
//            std::vector<char> buffer;
//            buffer.resize(decCs.length());
//            memcpy(buffer.data(), decCs.data(), decCs.length());
//            return buffer;
            return _ptr_to_arrays_1d<char>(decCs.data(), decCs.length());
        }
    }
    void writeFile(CString f1, py::array_t<char>& cs){
        std::ofstream fos;
        fos.open(f1, std::ios::binary);
        if(!fos.is_open()){
            fprintf(stderr, "open output failed: %s\n", f1.data());
            return;
        }
        fos.write(cs.data(), cs.size());
        fos.close();
    }
};

void BindImpl(pybind11::module& m);

PYBIND11_MODULE(PyEncDec, m) {
  m.doc() =
      "Make programer easier to use dec-file";
  BindImpl(m);
}

void BindImpl(pybind11::module& m){
    pybind11::class_<h7::PyEncDec>(m, "PyEncDec")
            .def(pybind11::init<>())
            .def("decFile",[](PyEncDec& self, CString f1){
                return self.decFile(f1);
            })
            .def("writeFile",[](PyEncDec& self, CString f1, py::array_t<char>& cs){
                self.writeFile(f1, cs);
            });
}

}
