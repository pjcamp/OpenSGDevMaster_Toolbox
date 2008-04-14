
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <typename AccessHandlerT, Int32 NamespaceI> inline
ChildPointerSFieldBase<AccessHandlerT, 
                       NamespaceI>::ChildPointerSFieldBase(
                           const FieldContainerPtr  pParent,
                                 UInt16             usChildFieldId,
                                 UInt16             usParentFieldId) :
      Inherited      (               ),
     _pEnclosingObj  (pParent        ),
     _childFieldId   (usChildFieldId ),
     _usParentFieldId(usParentFieldId)
{
}

template <typename AccessHandlerT, Int32 NamespaceI> inline
ChildPointerSFieldBase<AccessHandlerT, 
                       NamespaceI>::ChildPointerSFieldBase(
                                 const_value        value,
                           const FieldContainerPtr  pParent,
                                 UInt16             usChildFieldId,
                                 UInt16             usParentFieldId) : 
     Inherited      (               ),
    _pEnclosingObj  (pParent        ),
    _childFieldId   (usChildFieldId ),
    _usParentFieldId(usParentFieldId)
{
    this->ptrStoreSet(value);
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <typename AccessHandlerT, Int32 NamespaceI> inline
ChildPointerSFieldBase<AccessHandlerT, 
                       NamespaceI    >::~ChildPointerSFieldBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Child Linking Information                                               */

template <typename AccessHandlerT, Int32 NamespaceI> inline 
FieldContainerPtr 
    ChildPointerSFieldBase<AccessHandlerT, 
                           NamespaceI    >::getEnclosingObject(void) const
{
    return _pEnclosingObj;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerSFieldBase<AccessHandlerT, NamespaceI>::setEnclosingObject(
    const FieldContainerPtr pObj)
{
    _pEnclosingObj = pObj;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
UInt16 ChildPointerSFieldBase<AccessHandlerT, 
                              NamespaceI    >::getChildFieldId(void) const
{
    return _childFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerSFieldBase<AccessHandlerT, 
                            NamespaceI    >::setChildFieldId(
                                const UInt16 childFieldId)
{
    _childFieldId = childFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
UInt16 ChildPointerSFieldBase<AccessHandlerT, 
                              NamespaceI    >::getParentFieldId(void) const
{
    return _usParentFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerSFieldBase<AccessHandlerT, NamespaceI>::setParentFieldId(
    const UInt16 usParentFieldId)
{
    _usParentFieldId = usParentFieldId;
}

OSG_END_NAMESPACE
