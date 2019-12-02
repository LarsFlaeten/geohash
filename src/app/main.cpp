#include <iostream>

// From external libraries:
#include <cxxopts.hpp>

// From internal libs:
#include <geohash/Geohash.h>


int main(int argc, char** argv) {

	cxxopts::Options options(argv[0], "Simple Geohasher");
    options.add_options()
        ("h,help", "Print help")
        ("e, encode", "Encode a geohash from lat,lon[,acc] - default")
        ("d, decode", "Decode a geohash", cxxopts::value<std::string>())
        ("latitude", "Latitude", cxxopts::value<double>())
		("longitude", "Longitude", cxxopts::value<double>())
        ("accuracy", "Accuracy radius in meters", cxxopts::value<double>())
        ("v,verbose", "Verbose processing")
		("positional",
       "Positional arguments: these are the arguments that are entered "
       "without an option", cxxopts::value<std::vector<std::string>>());
        ;
	options.parse_positional({"latitude", "longitude", "accuracy", "positional"});
 	auto result = options.parse(argc, argv);
	   
    options.positional_help("latitude longitude [accuracy]");

    if(result.count("help"))
    {
        std::cout << options.help({""}) << std::endl;
        return 0;
    }

    bool verbose = false;
    if(result.count("verbose"))
        verbose = true;

    bool encode = false;
    bool decode = false;

    if(result.count("encode") && result.count("decode")) {
        std::cout << "Error, please supply either d(ecode) or e(ncode)" << std::endl;
        std::cout << options.help({""}) << std::endl;
        exit(1);
 
    }

    if(result.count("encode")) {
        encode = true;
        decode = false;
    }
    if(result.count("decode")) {
        encode = false;
        decode = true;
    }
    

    if(verbose)
        if(encode)
            std::cout << "Mode: encode" << std::endl;
        else if(decode)
            std::cout << "Mode: decode" << std::endl;
        else
            exit(0);

    if(encode && !result.count("latitude") || !result.count("longitude"))
    {
        std::cerr << "Latitude or longitude missing!" << std::endl;
        std::cout << options.help({""}) << std::endl;
        exit(1);
    } 
    
    geohash::Geohash hasher;

    if(encode) { 
        auto lat = result["latitude"].as<double>();
        auto lon = result["longitude"].as<double>(); 
        double accuracy = 0.0;
        if(result.count("accuracy"))
            accuracy = result["accuracy"].as<double>();


        if(verbose)
           std::cout << "Hashing posiiton: " << lat << ", " << lon << " (accuracy radius: " << accuracy << "m)" << std::endl; 


        if(verbose)
            std::cout << "Geohash: ";
        std::cout << hasher.encode(lat, lon, accuracy) << std::endl;
    }

    if(decode) {
        auto hash = result["decode"].as<std::string>();
        if(verbose)
            std::cout << "Decoding hash: " << hash << std::endl;
        

    }
    
    return 0;
}
