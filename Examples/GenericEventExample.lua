--[[
This lua script, if run somehow, will demonstrate the use of KabalaEngine's
generic event system.
]]--


--Get relevant userdata. What we're really after here is the Scene's event producer.
local project = KabalaEngine.ProjectRefPtr_dcast(OSG.getFieldContainer("Untitled Project"))
local scene = KabalaEngine.SceneRefPtr_dcast(project:getActiveScene())

--Some variables for local logic
local terminate = false
local count = 0

--Register local events and return an Id for the newly registered event.
--These Id's are what tell the generic event system what event to attach to.
local CountEvent = scene:registerNewGenericEvent("CountEvent")
local PrintEvent = scene:registerNewGenericEvent("PrintEvent")
local TerminateEvent = scene:registerNewGenericEvent("TerminateEvent")

--Print the Id's
OSG.LOG("RegisteredEventIds")
OSG.LOG(string.format("%i",CountEvent))
OSG.LOG(string.format("%i",PrintEvent))
OSG.LOG(string.format("%i",TerminateEvent))


local CountEventActivityConnection
local PrintEventActivityConnection
local TerminateEventActivityConnection

--Actually attach a lua function to an event.
CountEventActivityConnection = OSG.LuaActivity_addLuaCallback(scene,"CountEventFunction",CountEvent)
--This function takes in the object whose producer we want to attach to. In this case, it is the scene.
--The second argument is the name of the lua function to call when the event is fired.
--Finally, the Id of the event to attach to.
PrintEventActivityConnection = OSG.LuaActivity_addLuaCallback(scene,"PrintEventFunction",PrintEvent)
TerminateEventActivityConnection = OSG.LuaActivity_addLuaCallback(scene,"TerminateEventFunction",TerminateEvent)
--LuaActivity_addLuaCallback() returns the luaactivity it created.
--While not nessecary, this is stored in local data.

--Since an event with CountEventFunction as it's callback has already been added
--this function call does nothing.
OSG.LuaActivity_addLuaCallback(scene,"CountEventFunction",CountEvent)

--Enter event. Not part of the generic event system.
function tutorialEnterEvent(Event, EventId)
	OSG.LOG("in enter event")
end

--Update event. 'Main body loop' for this script.
function tutorialUpdateEvent(Event, EventId)
	OSG.LOG("in update event")
	local genericEvent = OSG.GenericEventDetailsRefPtr_dcast(OSG.createFieldContainer("GenericEventDetails"))
	
	if(scene:isGenericEventDefined(CountEvent)) then
		OSG.LOG("Firing Count Event")
--Firing an event is done with scene:produceGenericEvent(). It requires the Id of the event, as well as
--A genericEventPtr to hold the event data.
		scene:produceGenericEvent(CountEvent,genericEvent)
	end
end

--Count event. Called every time the update event is called. Increments count on each call.
--Fires PrintEvent every three counts.
--Fires TerminateEvent every twenty counts.
function CountEventFunction(Event, EventId)
	OSG.LOG("in count event")
	count = count + 1
	local genericEvent = OSG.GenericEventDetailsRefPtr_dcast(OSG.createFieldContainer("GenericEventDetails"))
	OSG.LOG(""..count);
	if(count%3 == 0) then
		OSG.LOG("Firing print event")
		scene:produceGenericEvent(PrintEvent,genericEvent)
	end
	if(count % 20 == 0) then
		OSG.LOG("Firing Terminate Event")
		scene:produceGenericEvent(TerminateEvent,genericEvent)
	end
end

--Prints Stuff
function PrintEventFunction(Event, EventId)
	OSG.LOG("Count TO 3!\n")
	OSG.LOG("EventId:"..EventId)
end

--The first time this is called it unregisters Count and PrintEvent, then
--reregisters and reattaches them.
--The second time it just unregisters those events and does not reattach them.
--By not reattaching them, it stops the cool part of this script. Only updateEvent is called.
function TerminateEventFunction(Event, EventId)
	OSG.LOG("Done!")
	
--Unregistering can be done by name or id
	scene:unregisterNewGenericEvent("CountEvent")
	scene:unregisterNewGenericEvent(PrintEvent)

 --Check to see if we've been here before
	if(not terminate) then
--Reregister everything just unregistered
		CountEvent = scene:registerNewGenericEvent("CountEvent")
		PrintEvent = scene:registerNewGenericEvent("PrintEvent")
		CountEventActivityConnection = OSG.LuaActivity_addLuaCallback(scene,"CountEventFunction",CountEvent)
		PrintEventActivityConnection = OSG.LuaActivity_addLuaCallback(scene,"PrintEventFunction",PrintEvent)
	end

--Flag as having been here before
	terminate = true
end
