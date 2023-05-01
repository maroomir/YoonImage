//
// Created by 윤철중 on 2023/05/01.
// https://github.com/aumuell/libjpeg-turbo/blob/master/example.c
//

#ifndef YOONFACTORY_JPEG_HPP
#define YOONFACTORY_JPEG_HPP

#include <cstdio>
#include <jpeglib.h>
#include <csetjmp>

namespace yoonfactory::image::jpeg {
    namespace {
        typedef struct error_manager {
            struct jpeg_error_mgr publisher{};
            jmp_buf buffer{};
        } error_manager_t;

        void jpeg_error_exit(j_common_ptr info) {
            auto * err = (error_manager_t *) info->err;
            (info->err->output_message)(info);
            longjmp(err->buffer, 1);
        }
    }

    static bool
    WriteJpegBuffer(const char *path, unsigned char *buffer, size_t width, size_t height, int channel, int quality = 100) {
        // JPEG 압축 정보 생성
        struct jpeg_compress_struct info{};
        struct jpeg_error_mgr manager{};
        info.err = jpeg_std_error(&manager);
        jpeg_create_compress(&info);
        // file 을 write mode 로 열고 압축 정보 저장
        FILE *file = fopen(path, "wb");
        if (!file) {
            std::cerr << "can't open file : " << path << std::endl;
            return false;
        }
        jpeg_stdio_dest(&info, file);
        info.image_width = width;
        info.image_height = height;
        switch (channel) {
            case 1:
                info.input_components = channel;
                info.in_color_space = JCS_GRAYSCALE;
                break;
            case 3:
                info.input_components = channel;
                info.in_color_space = JCS_RGB;
                break;
            default:
                std::cerr << "can't compose channel : " << channel << std::endl;
                return false;
        }
        jpeg_set_defaults(&info);
        jpeg_set_quality(&info, quality, true);
        jpeg_start_compress(&info, true);
        // JPEG buffer 정보 write
        size_t stride = width * channel;
        JSAMPROW row[1];
        while (info.next_scanline < info.image_height) {
            row[0] = &buffer[info.next_scanline * stride];
            (void) jpeg_write_scanlines(&info, row, 1);
        }

        jpeg_finish_compress(&info);
        fclose(file);
        jpeg_destroy_compress(&info);
        return true;
    }

    static unsigned char*
    ReadJpegBuffer(const char* path, size_t &width, size_t &height, size_t &channel) {
        // JPEG 압축 정보 읽어오기
        struct jpeg_decompress_struct info{};
        error_manager_t manager;
        // file 에서 JPEG 정보들을 read
        FILE *file = fopen(path, "rb");
        if (!file) {
            std::cerr << "can't open file : " << path << std::endl;
            return nullptr;
        }
        // JPEG 압축 정보를 가져오던 중 에러가 발생하는지 체크
        info.err = jpeg_std_error(&manager.publisher);
        manager.publisher.error_exit = jpeg_error_exit;
        if (setjmp(manager.buffer)) {
            jpeg_destroy_decompress(&info);
            fclose(file);
            return nullptr;
        }
        // JPEG 압축 정보 저장
        jpeg_create_decompress(&info);
        jpeg_stdio_src(&info, file);
        (void) jpeg_read_header(&info, true);
        (void) jpeg_start_decompress(&info);
        width = info.output_width;
        height = info.output_height;
        channel = info.output_components;
        size_t stride = width * channel;
        // JPEG buffer 정보 read
        JSAMPARRAY buffer = (*info.mem->alloc_sarray)
                ((j_common_ptr) &info, JPOOL_IMAGE, stride, 1);
        while (info.output_scanline < info.output_height) {
            (void) jpeg_read_scanlines(&info, buffer, 1);
        }

        (void) jpeg_finish_decompress(&info);
        jpeg_destroy_decompress(&info);
        fclose(file);
        return (unsigned char *) buffer;
    }
}

#endif //YOONFACTORY_JPEG_HPP
