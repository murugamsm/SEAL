// STD
#include <vector>

// SEALDll
#include "stdafx.h"
#include "ckksencoder.h"
#include "utilities.h"

// SEAL
#include "seal/ckks.h"

using namespace std;
using namespace seal;
using namespace seal::dll;


SEALDLL HRESULT SEALCALL CKKSEncoder_Create(void* context, void** ckks_encoder)
{
    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);
    IfNullRet(ckks_encoder, E_POINTER);

    try
    {
        CKKSEncoder* encoder = new CKKSEncoder(sharedctx);
        *ckks_encoder = encoder;
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL CKKSEncoder_Destroy(void* thisptr)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);

    delete encoder;
    return S_OK;
}

// Array of doubles
SEALDLL HRESULT SEALCALL CKKSEncoder_Encode1(void* thisptr, int value_count, double* values, uint64_t* parms_id, double scale, void* destination, void* pool)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    Plaintext* destinationptr = FromVoid<Plaintext>(destination);
    IfNullRet(destinationptr, E_POINTER);
    IfNullRet(parms_id, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    parms_id_type parms;
    CopyParmsId(parms_id, parms);

    vector<double> input(value_count);
    for (int i = 0; i < value_count; i++)
    {
        input[i] = values[i];
    }

    try
    {
        encoder->encode(input, parms, scale, *destinationptr, *handle);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

// Array of complex numbers (two doubles per value)
SEALDLL HRESULT SEALCALL CKKSEncoder_Encode2(void* thisptr, int value_count, double* complex_values, uint64_t* parms_id, double scale, void* destination, void* pool)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    Plaintext* destinationptr = FromVoid<Plaintext>(destination);
    IfNullRet(destinationptr, E_POINTER);
    IfNullRet(parms_id, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    parms_id_type parms;
    CopyParmsId(parms_id, parms);

    vector<complex<double>> input(value_count);
    for (int i = 0; i < value_count; i++)
    {
        input[i] = complex<double>(complex_values[i*2],
                                   complex_values[i*2 + 1]);
    }

    try
    {
        encoder->encode(input, parms, scale, *destinationptr, *handle);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

// Single double value
SEALDLL HRESULT SEALCALL CKKSEncoder_Encode3(void* thisptr, double value, uint64_t* parms_id, double scale, void* destination, void* pool)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    Plaintext* destinationptr = FromVoid<Plaintext>(destination);
    IfNullRet(destinationptr, E_POINTER);
    IfNullRet(parms_id, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    parms_id_type parms;
    CopyParmsId(parms_id, parms);

    try
    {
        encoder->encode(value, parms, scale, *destinationptr, *handle);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

// Single complex value
SEALDLL HRESULT SEALCALL CKKSEncoder_Encode4(void* thisptr, double real, double imaginary, uint64_t* parms_id, double scale, void* destination, void* pool)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    Plaintext* destinationptr = FromVoid<Plaintext>(destination);
    IfNullRet(destinationptr, E_POINTER);
    IfNullRet(parms_id, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    parms_id_type parms;
    CopyParmsId(parms_id, parms);

    complex<double> input(real, imaginary);

    try
    {
        encoder->encode(input, parms, scale, *destinationptr, *handle);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

// Single UInt64 value
SEALDLL HRESULT SEALCALL CKKSEncoder_Encode5(void* thisptr, uint64_t value, uint64_t* parms_id, void* destination)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    Plaintext* destinationptr = FromVoid<Plaintext>(destination);
    IfNullRet(destinationptr, E_POINTER);
    IfNullRet(parms_id, E_POINTER);

    parms_id_type parms;
    CopyParmsId(parms_id, parms);

    try
    {
        encoder->encode(value, parms, *destinationptr);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

// Array of doubles
SEALDLL HRESULT SEALCALL CKKSEncoder_Decode1(void* thisptr, void* plain, int* value_count, double* values, void* pool)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(value_count, E_POINTER);
    Plaintext* plainptr = FromVoid<Plaintext>(plain);
    IfNullRet(plainptr, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    vector<double> destination;

    try
    {
        encoder->decode(*plainptr, destination, *handle);
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }

    *value_count = static_cast<int>(destination.size());

    if (nullptr == values)
    {
        // We only wanted to know the size.
        return S_OK;
    }

    // Copy to actual destination
    for (int i = 0; i < destination.size(); i++)
    {
        values[i] = destination[i];
    }

    return S_OK;
}

// Array of complex numbers
SEALDLL HRESULT SEALCALL CKKSEncoder_Decode2(void* thisptr, void* plain, int* value_count, double* values, void* pool)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(value_count, E_POINTER);
    Plaintext* plainptr = FromVoid<Plaintext>(plain);
    IfNullRet(plainptr, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    vector<complex<double>> destination;

    try
    {
        encoder->decode(*plainptr, destination, *handle);
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }

    *value_count = static_cast<int>(destination.size());

    if (nullptr == values)
    {
        // We only wanted to know the size.
        return S_OK;
    }

    // Copy to actual destination
    for (int i = 0; i < destination.size(); i++)
    {
        values[i*2]     = destination[i].real();
        values[i*2 + 1] = destination[i].imag();
    }

    return S_OK;
}

SEALDLL HRESULT SEALCALL CKKSEncoder_SlotCount(void* thisptr, uint64_t* slot_count)
{
    CKKSEncoder* encoder = FromVoid<CKKSEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(slot_count, E_POINTER);

    *slot_count = encoder->slot_count();
    return S_OK;
}
