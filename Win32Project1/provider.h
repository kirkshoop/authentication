

namespace credentialprovider
{
	struct tag {};

	typedef 
		scenario::scenarios<smartcardlogon, scenario::unsupportedscenario, scenario::unsupportedscenario, scard_creduiscenario>
	type;
}

lib::ifset::traits_builder<lib::tv::factory<IUnknown, ICredentialProvider>::type, credentialprovider::type>
interface_set_traits(credentialprovider::tag&&);

template<typename Storage, typename InterfaceTag>
credentialprovider::type* interface_storage(Storage* storage, InterfaceTag&&, credentialprovider::tag&&)
{
	return storage;
}

typedef
	lib::ifset::interface_set<credentialprovider::tag>
provider;

namespace providerfactory
{
	struct tag {};
}

unique_hresult factory_create(IUnknown *pUnkOuter, REFIID riid, void **ppvObject, providerfactory::tag&&);


lib::ifset::traits_builder<lib::tv::factory<IUnknown, IClassFactory>::type, lib::com::classfactory<providerfactory::tag>>
interface_set_traits(providerfactory::tag&&);

template<typename Storage, typename InterfaceTag>
lib::com::classfactory<providerfactory::tag>* interface_storage(Storage* storage, InterfaceTag&&, providerfactory::tag&&)
{
	return storage;
}

typedef
	lib::ifset::interface_set<providerfactory::tag>
provider_factory;
