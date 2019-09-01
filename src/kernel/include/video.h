#ifndef OS_VIDEO_H
#define OS_VIDEO_H


class Video{
public:
    Video();
    ~Video();
    void clear();
    void write(char *cp);
    void put(char c);
private:
    unsigned short *videomem;
    unsigned int off;
    unsigned int pos;
};


#endif //OS_VIDEO_H