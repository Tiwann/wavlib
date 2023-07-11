#include <iostream>
#include <wavlib/generator.h>
#include <wavlib/wav.h>


int main(int argc, const char** argv)
{
    std::cout << "wavlib utilisation example.\n";

    wavlib::generators::sawtooth saw_generator(1.0, 440, 2.0);
    wavlib::wav wav = saw_generator.towav();
    if(!wav.write_to_file("test.wav"))
    {
        std::cout << "Failed to write file!\n";
    }

    wavlib::generators::powersine psine_generator(5, 1.0, 440, 1.0);
    wavlib::wav wav2 = psine_generator.towav();
    if(!wav2.write_to_file("test2.wav"))
    {
        std::cout << "Failed to write file!\n";
    }
    
    
    
    return 0;
}