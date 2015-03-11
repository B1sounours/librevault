/* Copyright (C) 2014-2015 Alexander Shishenko <GamePad64@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SRC_SYNC_OPENFSBLOCKSTORAGE_H_
#define SRC_SYNC_OPENFSBLOCKSTORAGE_H_

#include "BlockStorage.h"
#include <sqlite3.h>
#include <boost/filesystem.hpp>

namespace librevault {

class OpenFSBlockStorage : public BlockStorage {
	boost::filesystem::path directory_path;
	cryptodiff::key_t encryption_key;
	sqlite3* directory_db = 0;

	void index_file(const boost::filesystem::path& filepath);
public:
	OpenFSBlockStorage(const boost::filesystem::path& dirpath, const boost::filesystem::path& dbpath, cryptodiff::key_t key);
	virtual ~OpenFSBlockStorage();

	void init();
	void index();

	cryptodiff::FileMap get_FileMap(const boost::filesystem::path& filepath);
//	cryptodiff::FileMap get_FileMap(const boost::filesystem::path& filepath, std::string& signature);
	void put_FileMap(const boost::filesystem::path& filepath, const cryptodiff::FileMap& filemap, const std::string& signature);

	std::vector<uint8_t> get_block(const std::array<uint8_t, SHASH_LENGTH>& block_hash, cryptodiff::Block& block_meta);
	void put_block(const std::array<uint8_t, SHASH_LENGTH>& block_hash, const std::vector<uint8_t>& data);
};

} /* namespace librevault */

#endif /* SRC_SYNC_OPENFSBLOCKSTORAGE_H_ */
