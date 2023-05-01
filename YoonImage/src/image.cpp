//
// Created by maroomir on 2021-07-05.
//

#include "yoonimage/image.hpp"

using namespace yoonfactory;

Image::Image() {
    _width = image::default_width;
    _height = image::default_height;
    _channel = image::default_channel;
    _format = image::ToImageFormat(_channel);
    _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
    memset(_buffer, 0, sizeof(char) * _width * _height);
}

Image::Image(const Image &image) {
    _width = image._width;
    _height = image._height;
    _channel = image._channel;
    _format = image._format;
    _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
    memcpy(_buffer, image._buffer, sizeof(char) * _width * _height * _channel);
}


Image::Image(const std::string &image_path) {
    _width = image::default_width;
    _height = image::default_height;
    _channel = image::default_channel;
    _format = image::FORMAT_NONE;
    _buffer = nullptr;
    LoadBitmap(image_path);
}

Image::Image(size_t width, size_t height, size_t channel) {
    _width = width;
    _height = height;
    _channel = channel;
    _format = image::ToImageFormat(_channel);
    _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
    memset(_buffer, 0, sizeof(char) * _width * _height * _channel);
}

Image::Image(int* buffer, size_t width, size_t height) {
    _width = width;
    _height = height;
    _channel = 3;
    _format = image::ToImageFormat(_channel);
    _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
    for (int i = 0; i < width * height; i++) {
        unsigned char *pByte = ToByte(buffer[i]);
        memcpy(_buffer + i * _channel * sizeof(char), pByte, sizeof(char) * _channel);
        delete pByte;
    }
}

Image::Image(unsigned char *red_buffer, unsigned char *green_buffer, unsigned char *blue_buffer,
             size_t width, size_t height) {
    _width = width;
    _height = height;
    _channel = 3;
    _format = image::FORMAT_RGB;
    _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
    size_t size = _width * _height;
    size_t cursor = 0;
    memcpy(_buffer, red_buffer, sizeof(char) * size);
    cursor += sizeof(char) * size;
    memcpy(_buffer + (int)cursor, green_buffer, sizeof(char) * size);
    cursor += sizeof(char) * size;
    memcpy(_buffer + (int)cursor, blue_buffer, sizeof(char) * size);
}

Image::Image(unsigned char *buffer, size_t width, size_t height, image::IMAGE_FORMAT format) {
    _width = width;
    _height = height;
    _channel = ToChannel(format);
    switch (format) {
        case image::FORMAT_GRAY:
            _format = image::FORMAT_GRAY;
            _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
            memcpy(_buffer, buffer, sizeof(char) * _width * _height * _channel);
            break;
        case image::FORMAT_RGB:
        case image::FORMAT_RGB_PARALLEL:
            _format = image::FORMAT_RGB;
            _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
            memcpy(_buffer, buffer, sizeof(char) * _width * _height * _channel);
            break;
        case image::FORMAT_RGB_MIXED:  // Separate the pixel to Red, Green, Blue buffer
            _format = image::FORMAT_RGB;
            _buffer = _to_parallel_color_buffer(buffer);
            break;
        case image::FORMAT_BGR:
        case image::FORMAT_BGR_PARALLEL:
            _format = image::FORMAT_RGB;
            _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
            for (size_t c = 0; c < _channel; c++) {
                size_t start = (_channel - c - 1) * _width * _height;
                memcpy(_buffer + sizeof(char) * start, buffer + sizeof(char) * start,
                       sizeof(char) * _width * _height);
            }
            break;
        case image::FORMAT_BGR_MIXED:
            _format = image::FORMAT_RGB;
            _buffer = _to_parallel_color_buffer(buffer, true);
            break;
        default:
            std::printf("[Image] Abnormal Image Format\n");
            _format = image::FORMAT_GRAY;
            _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
            memset(_buffer, 0, sizeof(char) * _width * _height * _channel);
            break;
    }
}

Image::~Image() {
    if (!_buffer) {
        free(_buffer);
        _buffer = nullptr;
    }
}

unsigned char* Image::_to_parallel_color_buffer(const unsigned char *buffer, bool reverse_order) const {
    auto *result = static_cast<unsigned char *>(malloc(
            sizeof(char) * _width * _height * _channel));
    for (size_t c = 0; c < _channel; c++) {
        size_t start = c * _width * _height;
        size_t color = (reverse_order) ? _channel - c - 1 : c;  // BRG or RGB
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                result[start + y * _width + x] = buffer[y * _width * _channel + x * _channel + color];
            }
        }
    }
    return result;
}

unsigned char* Image::_to_mixed_color_buffer(const unsigned char *buffer, bool reverse_order) const {
    auto *result = static_cast<unsigned char *>(malloc(
            sizeof(char) * _width * _height * _channel));

    for (size_t c = 0; c < _channel; c++) {
        size_t start = c * _width * _height;
        size_t color = (reverse_order) ? _channel - c - 1 : c;
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                result[y * _width * _channel + x * _channel + color] = buffer[start + y * _width + x];
            }
        }
    }
    return result;
}

size_t Image::Width() const {
    return _width;
}

size_t Image::Height() const {
    return _height;
}

size_t Image::Channel() const {
    return _channel;
}

size_t Image::Stride() const {
    return _width * _channel;
}

unsigned char* Image::GetBuffer() {
    return _buffer;
}

unsigned char* Image::CopyBuffer() {
    auto* buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
    memcpy(buffer, _buffer, sizeof(char) * _width * _height * _channel);
    return buffer;
}

image::IMAGE_FORMAT Image::ImageFormat() {
    return _format;
}

unsigned char* Image::GetMixedColorBuffer() {
    unsigned char *buffer = nullptr;
    switch (_format) {
        case image::FORMAT_GRAY: {
            size_t size = _width * _height;
            buffer = static_cast<unsigned char *>(malloc(sizeof(char) * size * 3));
            for (int c = 0; c < 3; c++) {
                size_t offset = size * c;
                memcpy(buffer + sizeof(char) * offset, _buffer + sizeof(char) * offset, sizeof(char) * size);
            }
            break;
        }
        case image::FORMAT_RGB:
            buffer = _to_mixed_color_buffer(_buffer, true);
            break;
        case image::FORMAT_BGR:
            buffer = _to_mixed_color_buffer(_buffer, false);
            break;
        default:
            std::printf("[Image][GetMixedColorBuffer] Abnormal Image Format\n");
            break;
    }
    return buffer;
}

void Image::CopyFrom(const Image &image) {
    _width = image._width;
    _height = image._height;
    _channel = image._channel;
    _format = image._format;
    if (_buffer != nullptr) {
        free(_buffer);
        _buffer = nullptr;
    }
    _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
    memcpy(_buffer, image._buffer, sizeof(char) * _width * _height * _channel);
}

Image* Image::Clone() {
    return new Image(_buffer, _width, _height, _format);
}

bool Image::Equals(const Image &image) {
    bool equal = (_width == image._width) &&
                 (_height == image._height) &&
                 (_channel == image._channel) &&
                 (_format == image._format);
    if (equal) {
        size_t size = _width * _height * _channel;
        for (size_t i = 0; i < size; i++) {
            if (_buffer[i] != image._buffer[i]) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}

unsigned char* Image::ToGrayBuffer() {
    size_t size = _width * _height;
    auto *result = new unsigned char[sizeof(char) * size];
    switch (_format) {
        case image::FORMAT_GRAY:
            memcpy(result, _buffer, sizeof(char) * size);
            break;
        case image::FORMAT_RGB:
            for (size_t h = 0; h < _height; h++) {
                for (size_t w = 0; w < _width; w++) {
                    size_t pos = h * _width + w;
                    unsigned char red = _buffer[pos];
                    unsigned char green = _buffer[size + pos];
                    unsigned char blue = _buffer[2 * size + pos];
                    // ITU-RBT.709, YPrPb
                    result[pos] = (unsigned char) (0.299 * red + 0.587 * green + 0.114 * blue);
                }
            }
            break;
        case image::FORMAT_BGR:
            for (size_t h = 0; h < _height; h++) {
                for (size_t w = 0; w < _width; w++) {
                    size_t pos = h * _width + w;
                    unsigned char blue = _buffer[pos];
                    unsigned char green = _buffer[size + pos];
                    unsigned char red = _buffer[2 * size + pos];
                    // ITU-RBT.709, YPrPb
                    result[pos] = (unsigned char) (0.299 * red + 0.587 * green + 0.114 * blue);
                }
            }
            break;
        default:
            std::printf("[Image][ToGrayImage] Abnormal Image Format\n");
            memset(result, 0, sizeof(char) * size);
            break;
    }
    return result;
}

Image* Image::ToGrayImage() {
    unsigned char *result_buffer = ToGrayBuffer();
    auto *result_image = new Image(result_buffer, _width, _height, image::FORMAT_GRAY);
    delete[] result_buffer;
    return result_image;
}

unsigned char* Image::ToRedBuffer() {
    size_t size = _width * _height;
    auto *result = new unsigned char[sizeof(char) * size];
    switch (_format) {
        case image::FORMAT_GRAY:
        case image::FORMAT_RGB:  // "R" G B
            memcpy(result, _buffer, sizeof(char) * size);
            break;
        case image::FORMAT_BGR:  // B G "R"
            memcpy(result, _buffer + sizeof(char) * size * 2, sizeof(char) * size);
            break;
        default:
            std::printf("[Image][ToRedImage] Abnormal Image Format\n");
            memset(result, 0, sizeof(char) * size);
            break;
    }
    return result;
}

Image* Image::ToRedImage() {
    unsigned char *result_buffer = ToRedBuffer();
    auto *result_image = new Image(result_buffer, _width, _height, image::FORMAT_GRAY);
    delete[] result_buffer;
    return result_image;
}

unsigned char* Image::ToGreenBuffer() {
    size_t size = _width * _height;
    auto *result_buffer = new unsigned char[sizeof(char) * size];
    switch (_format) {
        case image::FORMAT_GRAY:
            memcpy(result_buffer, _buffer, sizeof(char) * size);
            break;
        case image::FORMAT_RGB:  // R "G" B
        case image::FORMAT_BGR:  // B "G" R
            memcpy(result_buffer, _buffer + sizeof(char) * size, sizeof(char) * size);
            break;
        default:
            std::printf("[Image][ToGreenImage] Abnormal Image Format\n");
            memset(result_buffer, 0, sizeof(char) * size);
            break;
    }
    return result_buffer;
}

Image* Image::ToGreenImage() {
    unsigned char* result_buffer = ToGreenBuffer();
    auto *result_image = new Image(result_buffer, _width, _height, image::FORMAT_GRAY);
    delete[] result_buffer;
    return result_image;
}

unsigned char* Image::ToBlueBuffer() {
    size_t size = _width * _height;
    auto *result_buffer = new unsigned char[sizeof(char) * size];
    switch (_format) {
        case image::FORMAT_GRAY:
        case image::FORMAT_BGR:  // "B" G R
            memcpy(result_buffer, _buffer, sizeof(char) * size);
            break;
        case image::FORMAT_RGB:  // R G "B"
            memcpy(result_buffer, _buffer + sizeof(char) * size * 2, sizeof(char) * size);
            break;
        default:
            std::printf("[Image][ToRedImage] Abnormal Image Format\n");
            memset(result_buffer, 0, sizeof(char) * size);
            break;
    }
    return result_buffer;
}

Image* Image::ToBlueImage() {
    unsigned char* result_buffer = ToBlueBuffer();
    auto *result_image = new Image(result_buffer, _width, _height, image::FORMAT_GRAY);
    delete[] result_buffer;
    return result_image;
}

bool Image::LoadBitmap(const std::string &path) {
    std::ifstream stream(path.c_str(), std::ios::binary);
    if (!stream) {
        std::printf("[Image][LoadBitmap] File Path is not correct\n");
        return false;
    }

    if (!_buffer) {
        free(_buffer);
        _buffer = nullptr;
    }
    _width = 0;
    _height = 0;
    _channel = 0;
    image::bitmap::bitmap_file_header file_header{};
    image::bitmap::bitmap_info_header info_header{};
    file_header.clear();
    info_header.clear();
    image::bitmap::ReadBitmapFileHeader(stream, file_header);
    image::bitmap::ReadBitmapInfoHeader(stream, info_header);
    if (info_header.size != info_header.header_size()) {
        std::printf("[Image][LoadBitmap] Invalid Bitmap Size\n");
        file_header.clear();
        info_header.clear();
        stream.close();
        // Initialize the buffer
        _width = image::default_width;
        _height = image::default_height;
        _channel = image::default_channel;
        _format = image::ToImageFormat(_channel);
        _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
        memset(_buffer, 0, sizeof(char) * _width * _height);
        return false;
    }

    _width = info_header.width;
    _height = info_header.height;
    _channel = info_header.bit_count >> 3;  // 00011000 => 00000011
    _format = image::ToImageFormat(_channel);
    try {
        if (_format == image::FORMAT_GRAY)
            image::bitmap::ReadBitmapPaletteTable(stream);
        unsigned char *buffer = image::bitmap::ReadBitmapBuffer(stream, _width, _height, _channel);
        _buffer = _to_parallel_color_buffer(buffer, true);
        delete[] buffer;
        stream.close();
    }
    catch (int code) {
        std::printf("[Image][LoadBitmap] Buffer Reading Error\n");
        file_header.clear();
        info_header.clear();
        stream.close();
        // Initialize the buffer
        _width = image::default_width;
        _height = image::default_height;
        _channel = image::default_channel;
        _format = image::ToImageFormat(_channel);
        _buffer = static_cast<unsigned char *>(malloc(sizeof(char) * _width * _height * _channel));
        memset(_buffer, 0, sizeof(char) * _width * _height);
        return false;
    }
    return true;
}

bool Image::SaveBitmap(const std::string &path) {
    std::ofstream stream(path.c_str(), std::ios::binary);
    if (!stream) {
        std::printf("[Image][SaveBitmap] File Path is not correct\n");
        return false;
    }
    if (!_buffer) {
        std::printf("[Image][SaveBitmap] Buffer is empty\n");
        return false;
    }

    image::bitmap::bitmap_info_header info_header{};
    info_header.width = _width;
    info_header.height = _height;
    info_header.bit_count = _channel << 3;  // 00000011 => 00011000
    info_header.compression = 0;
    info_header.planes = 1;
    info_header.size = info_header.header_size();
    info_header.xpels_per_meter = 0;
    info_header.ypels_per_meter = 0;
    info_header.buffer_size = (((info_header.width * _channel) + 3) & 0x0000FFFC) * info_header.height;
    info_header.important_color = 0;
    info_header.used_color = 0;
    image::bitmap::bitmap_file_header file_header{};
    file_header.type = 0x4D42;  // 0x4D42 (19778, Static Number)
    file_header.size = file_header.header_size() + info_header.header_size() + info_header.buffer_size;
    file_header.reserved1 = 0;
    file_header.reserved2 = 0;
    file_header.off_bits = info_header.header_size() + file_header.header_size();
    if (_format == image::FORMAT_GRAY)
        file_header.off_bits += sizeof(image::bitmap::rgbquad_palette) * 256;
    image::bitmap::WriteBitmapFileHeader(stream, file_header);
    image::bitmap::WriteBitmapInfoHeader(stream, info_header);

    size_t size = _width * _height;
    unsigned char *buffer;
    switch (_format) {
        case image::FORMAT_GRAY:
            // Palette Table
            image::bitmap::WriteBitmapPaletteTable(stream);
            // Pixel Buffer
            buffer = new unsigned char[sizeof(char) * size];
            memcpy(buffer, _buffer, sizeof(char) * size);
            break;
        case image::FORMAT_RGB:
        case image::FORMAT_RGB_PARALLEL:
            buffer = _to_mixed_color_buffer(_buffer, true);  // TO_BGR_MIXED
            break;
        case image::FORMAT_BGR:
        case image::FORMAT_BGR_PARALLEL:
            buffer = _to_mixed_color_buffer(_buffer, false);  // TO_BGR_MIXED
            break;
        case image::FORMAT_RGB_MIXED:
        case image::FORMAT_BGR_MIXED:
            buffer = new unsigned char[size * _channel];
            memcpy(buffer, _buffer, sizeof(char) * size * _channel);
            break;
        default:
            buffer = new unsigned char[size * _channel];
            memset(buffer, 0, sizeof(char) * size * _channel);
            break;
    }
    image::bitmap::WriteBitmapBuffer(stream, buffer, _width, _height, _channel);
    stream.close();
    delete[] buffer;
    return true;
}

bool Image::LoadJpeg(const std::string &path) {
    // buffer 는 mixed color buffer 로 읽어옴
    auto buffer = image::jpeg::ReadJpegBuffer(path.c_str(), _width, _height, _channel);
    if (!buffer) {
        _buffer = _to_parallel_color_buffer(buffer);
        _format = image::ToImageFormat(_channel);
        return true;
    }
    std::printf("[Image][LoadJpeg] Invalid jpeg path\n");
    return false;
}

bool Image::SaveJpeg(const std::string &path) {
    // jpeg 로 save 할 때는 mixed color buffer 사용해야함
    unsigned char *buffer = (_format != image::FORMAT_RGB_MIXED) ? _to_mixed_color_buffer(_buffer) : _buffer;
    if (!image::jpeg::WriteJpegBuffer(path.c_str(), buffer, _width, _height, (int) _channel)) {
        std::printf("[Image][SaveJpeg] Jpeg saved failed\n");
        return false;
    } else {
        return true;
    }
}

Image *Image::GrayPaletteBar(int width, int height, int step) {
    width *= step;
    auto *buffer = new unsigned char[width * height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer[y * width + x] = (unsigned char) (x / step);
        }
    }
    auto *result_image = new Image(buffer, width, height, image::FORMAT_GRAY);
    delete[] buffer;
    return result_image;
}

Image *Image::ColorPaletteBar(int width, int height, int step) {
    width *= step;
    int channel = 3;
    auto *red_buffer = new unsigned char[width * height * channel];
    auto *green_buffer = new unsigned char[width * height * channel];
    auto *blue_buffer = new unsigned char[width * height * channel];
    for (int y = 0; y < height; y++) {
        for (int page = 0; page < channel; page++) {
            for (int x = 0; x < width; x++) {
                int i = y * width * channel + page * width + x;
                switch (page) {
                    case 0:  // RED Area
                        red_buffer[i] = 255 - (unsigned char) (x / step);
                        green_buffer[i] = (unsigned char) (x / step);
                        blue_buffer[i] = 0;
                        break;
                    case 1: // GREEN Area
                        red_buffer[i] = 0;
                        green_buffer[i] = 255 - (unsigned char) (x / step);
                        blue_buffer[i] = (unsigned char) (x / step);
                        break;
                    case 2: // BLUE Area
                        red_buffer[i] = (unsigned char) (x / step);
                        green_buffer[i] = 0;
                        blue_buffer[i] = 255 - (unsigned char) (x / step);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    auto *result_image = new Image(red_buffer, green_buffer, blue_buffer, width * channel, height);
    delete[] red_buffer;
    delete[] green_buffer;
    delete[] blue_buffer;
    return result_image;
}

