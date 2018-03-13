#pragma once
#include <vector>
#include <unordered_map>
#include <string>

template <typename ... Ts>
class Callback
{
public:
	using CallbackFnType = void(*)(Ts...);
	using Name_fn_pair = std::pair<const char*, CallbackFnType>;

	void AddCallback(const char* _name, const CallbackFnType callbackFn)
	{
		Name_fn_pair newcb(_name, callbackFn);
		callbackFnAdd.push_back(newcb);
		callbackschanged = true;
	}

	void RemoveCallback(const char* _name)
	{
		Name_fn_pair remove(_name, nullptr);
		callbackFnRemove.push_back(remove);
		callbackschanged = true;
	}

	void Call(Ts... args)
	{
		if (callbackschanged)
			UpdateCallbacks();	// this will likely be called only on startup

		for each(Name_fn_pair callback in callbackFnList)
		{
			CallbackFnType func = callback.second;
			func(args...);
		}
	}

private:
	void UpdateCallbacks()
	{
		// Remove Callbacks 
		for each(Name_fn_pair elem_to_remove in callbackFnRemove)
		{
			int size = callbackFnList.size();
			for (int idx = 0; idx < size; idx++)
			{
				if (!strcmp(elem_to_remove.first, callbackFnList[idx].first)) // if names are equal
				{
					callbackFnList.erase(callbackFnList.begin() + idx);
					size--;
				}
			}
		}
		callbackFnRemove.clear();

		// Add Callbacks 
		// TODO: make it possible to add Callbacks at specific position
		for each(Name_fn_pair elem_to_add in callbackFnAdd)
		{
			callbackFnList.push_back(elem_to_add);
		}
		callbackFnAdd.clear();

		callbackschanged = false;
	}

private:
	bool callbackschanged;
	std::vector<Name_fn_pair> callbackFnList;
	std::vector<Name_fn_pair> callbackFnAdd;
	std::vector<Name_fn_pair> callbackFnRemove;
};