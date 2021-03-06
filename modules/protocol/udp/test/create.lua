-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.

-- Basic test that will create a new packet from scratch
local raw = require("protocol/raw")
local ipv4 = require("protocol/ipv4")
local udp = require("protocol/udp")

-- just to be safe, to avoid the test to run in an infinite loop
local counter = 10

haka.rule {
	hook = udp.events.receive_packet,
	eval = function (pkt)
		if pkt.srcport ~= 3333 then
			if counter == 0 then
				error("loop detected")
			end
			counter = counter-1

			local npkt = raw.create()
			npkt = ipv4.create(npkt)
			npkt.src = ipv4.addr(192, 168, 0, 1)
			npkt.dst = ipv4.addr("192.168.0.2")

			npkt = udp.create(npkt,
				{ srcport = 3333, dstport = 4444 })

			npkt:inject()
		end
	end
}
