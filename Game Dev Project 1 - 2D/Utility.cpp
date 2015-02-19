#include "Utility.h"
#include <zlib/zlib.h>
#include <Game Engine/Errors.h>

std::string Utility::Decompress(std::string& compressed)
{
	z_stream zs;                        // z_stream is zlib's control structure
	memset(&zs, 0, sizeof(zs));

	if (inflateInit(&zs) != Z_OK)
		throw(std::runtime_error("inflateInit failed while decompressing."));

	zs.next_in = (Bytef*)compressed.data();
	zs.avail_in = compressed.size();

	int ret;
	char outbuffer[32768];
	std::string outstring;

	// get the decompressed bytes blockwise using repeated calls to inflate
	do
	{
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = inflate(&zs, 0);

		if (outstring.size() < zs.total_out)
		{
			outstring.append(outbuffer,
				zs.total_out - outstring.size());
		}

	} while (ret == Z_OK);

	inflateEnd(&zs);

	if (ret != Z_STREAM_END)
	{          // an error occurred that was not EOF		
		std::string errorString = "Exception during zlib decompression: " + ret;
		errorString += ":";
		errorString += zs.msg;
		GameEngine::FatalError(errorString);
	}

	return outstring;
}
