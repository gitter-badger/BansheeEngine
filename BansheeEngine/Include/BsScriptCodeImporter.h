//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPrerequisites.h"
#include "BsSpecificImporter.h"

namespace BansheeEngine
{
	/**
	 * @brief	Imports C# script source code files (.cs).
	 */
	class BS_EXPORT ScriptCodeImporter : public SpecificImporter
	{
	public:
		ScriptCodeImporter();
		virtual ~ScriptCodeImporter();

		/** @copydoc SpecificImporter::isExtensionSupported */
		virtual bool isExtensionSupported(const WString& ext) const override;

		/** @copydoc SpecificImporter::isMagicNumberSupported */
		virtual bool isMagicNumberSupported(const UINT8* magicNumPtr, UINT32 numBytes) const override;

		/** @copydoc SpecificImporter::import */
		virtual ResourcePtr import(const Path& filePath, ConstImportOptionsPtr importOptions) override;

		/** @copydoc SpecificImporter::createImportOptions */
		virtual ImportOptionsPtr createImportOptions() const override;

		static const WString DEFAULT_EXTENSION;
	};
}