﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BansheeEngine;
 
namespace BansheeEditor
{
    /// <summary>
    /// Inspectable field displays GUI elements for a single <see cref="SerializableProperty"/>. This is a base class that
    /// should be specialized for all supported types contained by <see cref="SerializableProperty"/>. Inspectable fields
    /// can and should be created recursively - normally complex types like objects and arrays will contain fields of their 
    /// own, while primitive types like integer or boolean will consist of only a GUI element.
    /// </summary>
    public class InspectableField
    {
        private List<InspectableField> children = new List<InspectableField>();
        private InspectableField parent;
        
        protected InspectableFieldLayout layout;
        protected SerializableProperty property;
        protected string title;
        protected int depth;

        /// <summary>
        /// Creates a new inspectable field GUI for the specified property.
        /// </summary>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the array whose contents to display.</param>
        public InspectableField(string title, int depth, InspectableFieldLayout layout, SerializableProperty property)
        {
            this.layout = layout;
            this.title = title;
            this.property = property;
            this.depth = depth;
        }

        /// <summary>
        /// Registers an inspectable field as a child of this field. 
        /// </summary>
        /// <param name="child">Inspectable field to register as a child.</param>
        protected void AddChild(InspectableField child)
        {
            if (child.parent == this)
                return;

            if (child.parent != null)
                child.parent.RemoveChild(child);

            children.Add(child);
            child.parent = this;
        }

        /// <summary>
        /// Unregisters an inspectable field as a child of this field. Call this when manually destroying a child field.
        /// </summary>
        /// <param name="child">Inspectable field to unregister.</param>
        protected void RemoveChild(InspectableField child)
        {
            children.Remove(child);
            child.parent = null;
        }

        /// <summary>
        /// Checks if contents of the field have been modified, and updates them if needed.
        /// </summary>
        /// <param name="layoutIndex">Index in the parent's layout at which to insert the GUI elements for this field.</param>
        /// <returns>True if there were any modifications in this field, or any child fields.</returns>
        public virtual bool Refresh(int layoutIndex)
        {
            bool anythingModified = false;

            if (IsModified())
            {
                Update(layoutIndex);
                anythingModified = true;
            }

            int currentIndex = 0;
            for (int i = 0; i < children.Count; i++)
            {
                anythingModified |= children[i].Refresh(currentIndex);
                currentIndex += children[i].GetNumLayoutElements();
            }

            return anythingModified;
        }

        /// <summary>
        /// Returns the total number of GUI elements in the field's layout.
        /// </summary>
        /// <returns>Number of GUI elements in the field's layout.</returns>
        public int GetNumLayoutElements()
        {
            return layout.NumElements;
        }

        /// <summary>
        /// Returns an optional title layout. Certain fields may contain separate title and content layouts. Parent fields
        /// may use the separate title layout instead of the content layout to append elements. Having a separate title 
        /// layout is purely cosmetical.
        /// </summary>
        /// <returns>Title layout if the field has one, null otherwise.</returns>
        public virtual GUILayoutX GetTitleLayout()
        {
            return null;
        }

        /// <summary>
        /// Checks have the values in the referenced serializable property have been changed compare to the value currently
        /// displayed in the field.
        /// </summary>
        /// <returns>True if the value has been modified and needs updating.</returns>
        protected virtual bool IsModified()
        {
            return false;
        }

        /// <summary>
        /// Reconstructs the GUI by using the most up to date values from the referenced serializable property.
        /// </summary>
        /// <param name="layoutIndex">Index in the parent's layout at which to insert the GUI elements for this field.</param>
        protected virtual void Update(int layoutIndex)
        {
            // Destroy all children as we expect update to rebuild them
            InspectableField[] childrenCopy = children.ToArray();
            for (int i = 0; i < childrenCopy.Length; i++)
            {
                childrenCopy[i].Destroy();
            }

            children.Clear();
        }

        /// <summary>
        /// Returns an inspectable field at the specified index.
        /// </summary>
        /// <param name="index">Sequential index of the field.</param>
        /// <returns>Child inspectable field at the specified index.</returns>
        protected InspectableField GetChild(int index)
        {
            return children[index];
        }

        /// <summary>
        /// Number of child inspectable fields.
        /// </summary>
        protected int ChildCount
        {
            get { return children.Count; }
        }

        /// <summary>
        /// Destroys all GUI elements in the inspectable field.
        /// </summary>
        public virtual void Destroy()
        {
            layout.DestroyElements();

            InspectableField[] childrenCopy = children.ToArray();
            for (int i = 0; i < childrenCopy.Length; i++)
                childrenCopy[i].Destroy();

            children.Clear();

            if (parent != null)
                parent.RemoveChild(this);
        }

        /// <summary>
        /// Creates a new inspectable field, automatically detecting the most appropriate implementation for the type
        /// contained in the provided serializable property. This may be one of the built-in inspectable field implemetations
        /// (like ones for primitives like int or bool), or a user defined implementation defined with a 
        /// <see cref="CustomInspector"/> attribute.
        /// </summary>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the array whose contents to display.</param>
        /// <returns>Inspectable field implementation that can be used for displaying the GUI for a serializable property
        ///          of the provided type.</returns>
        public static InspectableField CreateInspectable(string title, int depth, InspectableFieldLayout layout, SerializableProperty property)
        {
            Type customInspectable = InspectorUtility.GetCustomInspectable(property.InternalType);
            if (customInspectable != null)
            {
                return (InspectableField)Activator.CreateInstance(customInspectable, depth, title, property);
            }

            switch (property.Type)
            {
                case SerializableProperty.FieldType.Int:
                    return new InspectableInt(title, depth, layout, property);
                case SerializableProperty.FieldType.Float:
                    return new InspectableFloat(title, depth, layout, property);
                case SerializableProperty.FieldType.Bool:
                    return new InspectableBool(title, depth, layout, property);
                case SerializableProperty.FieldType.Color:
                    return new InspectableColor(title, depth, layout, property);
                case SerializableProperty.FieldType.String:
                    return new InspectableString(title, depth, layout, property);
                case SerializableProperty.FieldType.Vector2:
                    return new InspectableVector2(title, depth, layout, property);
                case SerializableProperty.FieldType.Vector3:
                    return new InspectableVector3(title, depth, layout, property);
                case SerializableProperty.FieldType.Vector4:
                    return new InspectableVector4(title, depth, layout, property);
                case SerializableProperty.FieldType.ResourceRef:
                    return new InspectableResourceRef(title, depth, layout, property);
                case SerializableProperty.FieldType.GameObjectRef:
                    return new InspectableGameObjectRef(title, depth, layout, property);
                case SerializableProperty.FieldType.Object:
                    return new InspectableObject(title, depth, layout, property);
                case SerializableProperty.FieldType.Array:
                    return new InspectableArray(title, depth, layout, property);
                case SerializableProperty.FieldType.List:
                    return new InspectableList(title, depth, layout, property);
            }

            throw new Exception("No inspector exists for the provided field type.");
        }
    }
}