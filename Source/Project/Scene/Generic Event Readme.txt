There are four parts to the generic event system. They are registration, linking, producing, and unregistering.
Registration creates space for a new generic event, but is not sufficient to fire one.
Linking links a lua callback to an event Id. This Id does not have to be for a generic event.
Producing actually fires of a generic event.
Unregistering removes the id from being available, and unlinks it. Any event trying to use a removed Id will do nothing.

I. Registration
	Registration is required for a scene to be aware of what events are
available to it. The Id's are continually incrementing, and so a maximum
of around 4 million events can be registered. Once an Id has been unregistered,
it cannot be reused. All generic events must be registered.
	
	Registering is done with Scene:registerNewGenericMethod(String EventName),
where Scene is any scene object, and EventName is the name of the event.This
function returns the Id of the newly registered event. It is required that
this Id be saved for later use. This Id can then be used to link and produce
this new generic event.

Ex:

local myNewGenricEventId = Scene:registerNewGenericMethod("MyNewGenericEvent")

II. Linking
	This step, along with registering, is responsible for getting everything
set up. For any registered Id, a lua activity must be added to a field 
container's EventProducer in order to actually be fired. This step is simplified with 
OSG.LuaActivity_addLuaCallback(FieldContainerPtr producerObj,String luaCallBackName,UInt32 eventId)
If it appears that the callback has already been added for this Id, the function exits
and does nothing.

	Given some producer object, this function creates an activity that will call a
lua function with the given name any time and event with the given Id is fired. It returns
the lua activity, but saving the activity is not required.

Ex:

OSG.LuaActivity_addLuaCallback(Scene,"MyNewGenericEventFunction",myNewGenricEventId))

III. Producing
	Firing a generic event requires the creation of a new GenericEventPtr,
and setting that GenericEventPtr's source to be the producer object.
The GenericEventPtr is passed into the function that produces the event, along
with the Id of the event to fire off.

Ex:

	local genericEvent = OSG.GenericEventPtr_dcast(OSG.createFieldContainer("GenericEvent"))
	genericEvent.setField("Source",producerObject)
	scene:produceGenericEvent(myNewGenricEventId,genericEvent)
	
IV. Unregistering
	Any registered event can be unregistered. An unregistered event Id will no longer
be produceed, even if scene:produceGenericEvent() is called with the Id. Even with
protection, attempting to fire an unregistered event should be avoided. Unregistering
can be done by name or Id.

Ex:

	scene:unregisterNewGenericMethod("myNewGenricEvent")
	scene:unregisterNewGenericMethod(myNewGenricEventId)
	
V. Example Implementation
	See the file in this directory titled GenericEventExample.lua