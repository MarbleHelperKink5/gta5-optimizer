#include "adapters/win32_process_adapter.hpp"

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

namespace gta5opt::adapters {

std::optional<uint32_t> find_process_by_name(const std::string& name) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return std::nullopt;

    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);
    std::optional<uint32_t> result;
    if (Process32FirstW(snap, &pe)) {
        do {
            std::wstring wname(pe.szExeFile);
            std::string narrow(wname.begin(), wname.end());
            if (narrow == name) { result = pe.th32ProcessID; break; }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return result;
}

void* open_process_for_rw(uint32_t pid) {
    return OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION,
                       FALSE, pid);
}

void close_handle(void* handle) {
    if (handle) CloseHandle(static_cast<HANDLE>(handle));
}

std::optional<uintptr_t> module_base(uint32_t pid, const std::string& module) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snap == INVALID_HANDLE_VALUE) return std::nullopt;
    MODULEENTRY32W me{};
    me.dwSize = sizeof(me);
    std::optional<uintptr_t> result;
    if (Module32FirstW(snap, &me)) {
        do {
            std::wstring wname(me.szModule);
            std::string narrow(wname.begin(), wname.end());
            if (narrow == module) { result = reinterpret_cast<uintptr_t>(me.modBaseAddr); break; }
        } while (Module32NextW(snap, &me));
    }
    CloseHandle(snap);
    return result;
}

std::optional<size_t> module_size(uint32_t pid, const std::string& module) {
    auto base = module_base(pid, module);
    if (!base) return std::nullopt;
    HANDLE h = open_process_for_rw(pid);
    if (!h) return std::nullopt;
    MODULEINFO info{};
    BOOL ok = GetModuleInformation(static_cast<HANDLE>(h), reinterpret_cast<HMODULE>(*base), &info, sizeof(info));
    close_handle(h);
    if (!ok) return std::nullopt;
    return static_cast<size_t>(info.SizeOfImage);
}

bool read_memory(void* handle, uintptr_t addr, void* out, size_t size) {
    SIZE_T read = 0;
    return ReadProcessMemory(static_cast<HANDLE>(handle), reinterpret_cast<LPCVOID>(addr), out, size, &read) && read == size;
}

bool write_memory(void* handle, uintptr_t addr, const void* in, size_t size) {
    SIZE_T written = 0;
    return WriteProcessMemory(static_cast<HANDLE>(handle), reinterpret_cast<LPVOID>(addr), in, size, &written) && written == size;
}

unsigned long last_error() { return GetLastError(); }

} // namespace gta5opt::adapters