// SEALDll
#include "stdafx.h"
#include "ciphertext.h"
#include "utilities.h"

// SEAL
#include "seal/ciphertext.h"

using namespace std;
using namespace seal;
using namespace seal::dll;

namespace seal
{
    /**
    Enables access to private members of seal::Ciphertext.
    */
    struct Ciphertext::CiphertextPrivateHelper
    {
        static void resize(seal::Ciphertext *ciphertext, size_t size, size_t poly_modulus_degree,
            size_t coeff_mod_count)
        {
            ciphertext->resize_internal(size, poly_modulus_degree, coeff_mod_count);
        }
    };
}


SEALDLL HRESULT SEALCALL Ciphertext_Create1(void* memoryPoolHandle, void** ciphertext)
{
    IfNullRet(ciphertext, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(memoryPoolHandle);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    try
    {
        Ciphertext* cipher = new Ciphertext(*handle);
        *ciphertext = cipher;
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Create2(void* copy, void** ciphertext)
{
    Ciphertext* copyptr = FromVoid<Ciphertext>(copy);
    IfNullRet(copyptr, E_POINTER);
    IfNullRet(ciphertext, E_POINTER);

    Ciphertext* cipher = new Ciphertext(*copyptr);
    *ciphertext = cipher;
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_Create3(void* context, void* pool, void** ciphertext)
{
    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);
    IfNullRet(ciphertext, E_POINTER);
    MemoryPoolHandle* pool_ptr = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == pool_ptr)
        pool_ptr = &MemoryManager::GetPool();

    try
    {
        Ciphertext* cipher = new Ciphertext(sharedctx, *pool_ptr);
        *ciphertext = cipher;
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Create4(void* context, uint64_t* parms_id, void* pool, void** ciphertext)
{
    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);
    IfNullRet(parms_id, E_POINTER);
    IfNullRet(ciphertext, E_POINTER);
    MemoryPoolHandle* pool_ptr = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == pool_ptr)
        pool_ptr = &MemoryManager::GetPool();

    try
    {
        parms_id_type parmsid;
        CopyParmsId(parms_id, parmsid);

        Ciphertext* cipher = new Ciphertext(sharedctx, parmsid, *pool_ptr);
        *ciphertext = cipher;
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Create5(void* context, uint64_t* parms_id, int capacity, void* pool, void** ciphertext)
{
    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);
    IfNullRet(parms_id, E_POINTER);
    IfNullRet(ciphertext, E_POINTER);
    MemoryPoolHandle* pool_ptr = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == pool_ptr)
        pool_ptr = &MemoryManager::GetPool();

    try
    {
        parms_id_type parmsid;
        CopyParmsId(parms_id, parmsid);

        Ciphertext* cipher = new Ciphertext(sharedctx, parmsid, capacity, *pool_ptr);
        *ciphertext = cipher;
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Reserve1(void* thisptr, void* context, uint64_t* parms_id, int size_capacity)
{
    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(parms_id, E_POINTER);

    parms_id_type parms;
    CopyParmsId(parms_id, parms);

    try
    {
        cipher->reserve(sharedctx, parms, size_capacity);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Reserve2(void* thisptr, void* context, int size_capacity)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);

    try
    {
        cipher->reserve(sharedctx, size_capacity);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Reserve3(void* thisptr, int size_capacity)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    try
    {
        cipher->reserve(size_capacity);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Set(void* thisptr, void* assign)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    Ciphertext* assignptr = FromVoid<Ciphertext>(assign);
    IfNullRet(assignptr, E_POINTER);

    *cipher = *assignptr;
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_Destroy(void* thisptr)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    delete cipher;
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_UInt64Count(void* thisptr, int* uint64_count)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(uint64_count, E_POINTER);

    *uint64_count = static_cast<int>(cipher->uint64_count());
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_UInt64CountCapacity(void* thisptr, int* uint64_count_capacity)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(uint64_count_capacity, E_POINTER);

    *uint64_count_capacity = static_cast<int>(cipher->uint64_count_capacity());
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_Size(void* thisptr, int* size)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(size, E_POINTER);

    *size = static_cast<int>(cipher->size());
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_SizeCapacity(void* thisptr, int* size_capacity)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(size_capacity, E_POINTER);

    *size_capacity = static_cast<int>(cipher->size_capacity());
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_PolyModulusDegree(void* thisptr, int* poly_modulus_degree)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(poly_modulus_degree, E_POINTER);

    *poly_modulus_degree = static_cast<int>(cipher->poly_modulus_degree());
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_CoeffModCount(void* thisptr, int* coeff_mod_count)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(coeff_mod_count, E_POINTER);

    *coeff_mod_count = static_cast<int>(cipher->coeff_mod_count());
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_ParmsId(void* thisptr, uint64_t* parms_id)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(parms_id, E_POINTER);

    for (int i = 0; i < cipher->parms_id().size(); i++)
    {
        parms_id[i] = cipher->parms_id()[i];
    }

    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_SetParmsId(void* thisptr, uint64_t* parms_id)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(parms_id, E_POINTER);

    memcpy(cipher->parms_id().data(), parms_id, sizeof(uint64_t) * cipher->parms_id().size());
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_Resize1(void* thisptr, void* context, uint64_t* parms_id, int size)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);

    parms_id_type parms;
    memcpy(parms.data(), parms_id, sizeof(uint64_t) * parms.size());

    try
    {
        cipher->resize(sharedctx, parms, size);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Resize2(void* thisptr, void* context, int size)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx.get(), E_POINTER);

    try
    {
        cipher->resize(sharedctx, size);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Resize3(void* thisptr, int size)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    try
    {
        cipher->resize(size);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_Resize4(void* thisptr, int size, int polyModulusDegree, int coeffModCount)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    try
    {
        Ciphertext::CiphertextPrivateHelper::resize(cipher, size, polyModulusDegree, coeffModCount);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_GetDataAt1(void* thisptr, int index, uint64_t* data)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(data, E_POINTER);

    try
    {
        *data = (*cipher)[index];
        return S_OK;
    }
    catch (const out_of_range&)
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_INDEX);
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_GetDataAt2(void* thisptr, int poly_index, int coeff_index, uint64_t* data)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(data, E_POINTER);

    auto poly_uint64_count = util::mul_safe(
        cipher->poly_modulus_degree(), cipher->coeff_mod_count());

    // poly_index is verified by the data method, we need to verify coeff_index ourselves.
    if (coeff_index < 0 || coeff_index >= poly_uint64_count)
        return HRESULT_FROM_WIN32(ERROR_INVALID_INDEX);

    try
    {
        *data = cipher->data(poly_index)[coeff_index];
        return S_OK;
    }
    catch (const out_of_range&)
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_INDEX);
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_SetDataAt(void* thisptr, int index, uint64_t value)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    try
    {
        (*cipher)[index] = value;
        return S_OK;
    }
    catch (const out_of_range&)
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_INDEX);
    }
}

SEALDLL HRESULT SEALCALL Ciphertext_IsNTTForm(void* thisptr, bool* is_ntt_form)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(is_ntt_form, E_POINTER);

    *is_ntt_form = cipher->is_ntt_form();
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_Scale(void* thisptr, double* scale)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);
    IfNullRet(scale, E_POINTER);

    *scale = cipher->scale();
    return S_OK;
}

SEALDLL HRESULT SEALCALL Ciphertext_Release(void* thisptr)
{
    Ciphertext* cipher = FromVoid<Ciphertext>(thisptr);
    IfNullRet(cipher, E_POINTER);

    cipher->release();
    return S_OK;
}
