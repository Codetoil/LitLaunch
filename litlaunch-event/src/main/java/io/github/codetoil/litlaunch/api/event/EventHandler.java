/*
 * Copyright (C) 2019-2023 Codetoil
 * Contact me on Discord: @Codetoil#7253, or by Email: ianthisawesomee@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

package io.github.codetoil.litlaunch.api.event;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class EventHandler
{
    public final String NAME;
    private final Queue<IEventListener> eventListenersToAdd = new ArrayDeque<>();
    private final Queue<IEventListener> eventListenersToRemove = new ArrayDeque<>();
    private final List<IEventListener> _listeners = new ArrayList<>();

    public EventHandler(String name) {
        this.NAME = name;
        updateListenersFromQueue();
    }

    @Override
    public String toString() {
        return NAME + "{" + eventListenersToAdd + "," + eventListenersToRemove + "," + _listeners + "}";
    }

    private synchronized void updateListenersFromQueue() {
        while (!eventListenersToAdd.isEmpty()) {
            IEventListener listener = eventListenersToAdd.poll();
            _listeners.add(listener);
        }
        while (!eventListenersToRemove.isEmpty()) {
            IEventListener listener = eventListenersToRemove.poll();
            _listeners.remove(listener);
        }
    }

    public synchronized void addListener(IEventListener e) {
        eventListenersToAdd.offer(e);
    }

    public synchronized void removeListener(IEventListener e) {
        eventListenersToRemove.offer(e);
    }

    public synchronized void post(IEvent pEvent) {
        post(pEvent, false);
    }

    public synchronized void post(IEvent event, boolean isSpammy) {
        updateListenersFromQueue();
        for (IEventListener listener : this._listeners) {
            listener.receivedEvent(event, this);
        }
    }

    public interface IEventListener
    {
        void receivedEvent(IEvent event, EventHandler handler);
    }
}
