#pragma once


#include <vector>
#include <atlbase.h>
#include "SevenZipLibrary.h"
#include "FileInfo.h"
#include "CompressionFormat.h"
#include "CompressionLevel.h"
#include "ProgressCallback.h"


namespace SevenZip
{
	class SevenZipCompressor
	{
	private:

		const SevenZipLibrary& m_library;
		TString m_archivePath;
      CompressionFormatEnum m_compressionFormat;
		CompressionLevelEnum m_compressionLevel;

	public:

		SevenZipCompressor( const SevenZipLibrary& library, const TString& archivePath );
		virtual ~SevenZipCompressor();

		void SetCompressionFormat( const CompressionFormatEnum& format );
		void SetCompressionLevel( const CompressionLevelEnum& level );

		// Includes the last directory as the root in the archive, e.g. specifying "C:\Temp\MyFolder"
		// makes "MyFolder" the single root item in archive with the files within it included.
		virtual bool CompressDirectory( const TString& directory, ProgressCallback* callback, bool includeSubdirs = true);

		// Excludes the last directory as the root in the archive, its contents are at root instead. E.g.
		// specifying "C:\Temp\MyFolder" make the files in "MyFolder" the root items in the archive.
		virtual bool CompressFiles( const TString& directory, const TString& searchFilter, ProgressCallback* callback, bool includeSubdirs = true );
		virtual bool CompressAllFiles( const TString& directory, ProgressCallback* callback, bool includeSubdirs = true );

		// Compress just this single file as the root item in the archive.
		virtual bool CompressFile( const TString& filePath, ProgressCallback* callback);

	private:

		CComPtr< IStream > OpenArchiveStream();
		bool FindAndCompressFiles(	const TString& directory, const TString& searchPattern, 
									const TString& pathPrefix, bool recursion, ProgressCallback* callback);
		bool CompressFilesToArchive(const TString& pathPrefix, const std::vector< intl::FilePathInfo >& filePaths, ProgressCallback* callback);
		bool SetCompressionProperties( IUnknown* outArchive );
	};
}
