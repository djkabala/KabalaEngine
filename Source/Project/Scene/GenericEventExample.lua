--[[
This lua script, if run somehow, will demonstrate the use of KabalaEngine's
generic event system.
]]--


--Get relevant userdata. What we're really after here is the Scene's event producer.
local project = KabalaEngine.ProjectPtr_dcast(OSG.getFieldContainer("Metablast Project"))
local scene = KabalaEngine.ScenePtr_dcast(project:getActiveScene())
local producer = scene:getEventProducer()

--Some variables for local logic
local terminate = false
local count = 0

--Register local events and return an Id for the newly registered event.
--These Id's are what tell the generic event system what event to attach to.
local CountEvent = scene:registerNewGenericMethod("CountEvent")
local PrintEvent = scene:registerNewGenericMethod("PrintEvent")
local TerminateEvent = scene:registerNewGenericMethod("TerminateEvent")

--Print the Id's
print("RegisteredEventIds")
print(CountEvent)
print(PrintEvent)
print(TerminateEvent)


local CountEventActivity
local PrintEventActivity
local TerminateEventActivity

--Actually attach a lua function to an event.
CountEventActivity = OSG.LuaActivityPtr_dcast(OSG.LuaActivity_addLuaCallback(scene,"CountEventFunction",CountEvent))
--This function takes in the object whose producer we want to attach to. In this case, it is the scene.
--The second argument is the name of the lua function to call when the event is fired.
--Finally, the Id of the event to attach to.
PrintEventActivity = OSG.LuaActivityPtr_dcast(OSG.LuaActivity_addLuaCallback(scene,"PrintEventFunction",PrintEvent))
TerminateEventActivity = OSG.LuaActivityPtr_dcast(OSG.LuaActivity_addLuaCallback(scene,"TerminateEventFunction",TerminateEvent))
--LuaActivity_addLuaCallback() returns the luaactivity it created.
--While not nessecary, this is stored in local data.

--Since an event with CountEventFunction as it's callback has already been added
--this function call does nothing.
OSG.LuaActivityPtr_dcast(OSG.LuaActivity_addLuaCallback(scene,"CountEventFunction",CountEvent))

--Enter event. Not part of the generic event system.
function tutorialEnterEvent(Event, MethodId)
	print("in enter event")
end

--Update event. 'Main body loop' for this script.
function tutorialUpdateEvent(Event, MethodId)
	print("in update event")
	local genericEvent = OSG.GenericEventPtr_dcast(OSG.createFieldContainer("GenericEvent"))
	
	if(scene:isGenericMethodDefined(CountEvent)) then
		print("Firing Count Event")
--Firing an event is done with scene:produceGenericEvent(). It requires the Id of the event, as well as
--A genericEventPtr to hold the event data.
		scene:produceGenericEvent(CountEvent,genericEvent)
	end
end

--Count event. Called every time the update event is called. Increments count on each call.
--Fires PrintEvent every three counts.
--Fires TerminateEvent every twenty counts.
function CountEventFunction(Event, MethodId)
	print("in count event")
	count = count + 1
	local genericEvent = OSG.GenericEventPtr_dcast(OSG.createFieldContainer("GenericEvent"))
	print(count);
	if(count%3 == 0) then
		print("Firing print event")
		scene:produceGenericEvent(PrintEvent,genericEvent)
	end
	if(count % 20 == 0) then
		print("Firing Terminate Event")
		scene:produceGenericEvent(TerminateEvent,genericEvent)
	end
end

--Prints Stuff
function PrintEventFunction(Event, MethodId)
	print("Count TO 3!\n")
	print("MethodId:"..MethodId)
end

--The first time this is called it unregisters Count and PrintEvent, then
--reregisters and reattaches them.
--The second time it just unregisters those events and does not reattach them.
--By not reattaching them, it stops the cool part of this script. Only updateEvent is called.
function TerminateEventFunction(Event, MethodId)
	print("Done!")
	
--Unregistering can be done by name or id
	scene:unregisterNewGenericMethod("CountEvent")
	scene:unregisterNewGenericMethod(PrintEvent)

 --Check to see if we've been here before
	if(not terminate) then
--Reregister everything just unregistered
		CountEvent = scene:registerNewGenericMethod("CountEvent")
		PrintEvent = scene:registerNewGenericMethod("PrintEvent")
		CountEventActivity = OSG.LuaActivityPtr_dcast(OSG.LuaActivity_addLuaCallback(scene,"CountEventFunction",CountEvent))
		PrintEventActivity = OSG.LuaActivityPtr_dcast(OSG.LuaActivity_addLuaCallback(scene,"PrintEventFunction",PrintEvent))
	end

--Flag as having been here before
	terminate = true
end
