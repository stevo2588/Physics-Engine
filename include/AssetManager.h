#ifndef ASSETMANAGER
#define ASSETMANAGER

#include <tuple>
#include <map>
#include <algorithm>

// TODO POSSIBLY: is there a way, given only base classes, to get all non-abstract
// derived classes? That'd be cool
template <typename... Args>
class AssetManager {
public:
	AssetManager() {

	}

	// Add an asset to the manager
	template <typename T>
	bool add(T asset, std::string name) {

		// check if type T exists in the tuple
		// TODO: this doesn't seem to return false when it should...
		if(Index<std::map<std::string, T>, assetTuple>::value < 0) return false;

		// check if name already exists for this type
		if(std::get<Index<std::map<std::string, T>, assetTuple>::value>(assets).count(name) == 1) return false;

		// add the asset
		std::get< Index<std::map<std::string, T>, assetTuple>::value >(assets).emplace(name, asset);

		return true;
	}


	// get a raw pointer to an asset of type T, with given name
	template <typename T>
	T* get(std::string name) {
		// check if type T exists in the tuple
		if(Index<std::map<std::string, T>, assetTuple>::value < 0) return NULL;

		// make sure name exists for this type
		if(std::get<Index<std::map<std::string, T>, assetTuple>::value>(assets).count(name) != 1) return NULL;

		return &std::get< Index<std::map<std::string, T>, assetTuple>::value >(assets).at(name);
		//return &std::get< Index<std::map<std::string, T>, assetTuple>::value >(assets)[name];
	}


	private:

	//----- BEGIN ugly metaprogramming black magic ---------------------------
	// Used to get index of tuple given a type
	template <typename T, typename Tuple>
	struct Index;

	template <typename T>
	struct Index<T, std::tuple<> > {
		static const int value = std::numeric_limits<int>::min();
	};

	template <typename T, typename... Types>
	struct Index<T, std::tuple< T, Types...> > {
		static const int value = 0;
	};

	template <typename T, typename U, typename... Types>
	struct Index<T, std::tuple< U, Types...> > {
		static const int value = 1 + Index<T, std::tuple< Types... > >::value;
	};
	//----- END black magic ---------------------------------------------------



	// number of types of objects this AssetManager is managing
	static const unsigned short int typeCount = sizeof...(Args);

	// TODO POSSIBLY: if assets need more than name and object, consider multimaps
	// tuple of vectors, each with a different asset type
	typedef std::tuple< std::map< std::string, Args >... > assetTuple;
	assetTuple assets;
};


#endif // ASSETMANAGER

