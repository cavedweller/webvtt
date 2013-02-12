#include <webvttxx/node>
#include <webvttxx/nodefactory>

namespace WebVTT
{

const InternalNode *Node::toInternalNode() const
{
  if( WEBVTT_IS_VALID_INTERNAL_NODE( this->kind() ) )
  { return ( const InternalNode * )this; }
  else
  { throw "Invalid cast to InternalNode."; }
}

const TextNode *Node::toTextNode() const
{
  if( this->kind() == Node::Text )
  { return ( const TextNode * )this; }
  else
  { throw "Invalid cast to TextNode."; }
}

const TimeStampNode *Node::toTimeStampNode() const
{
  if( this->kind() == Node::TimeStamp )
  { return ( const TimeStampNode * )this; }
  else
  { throw "Invalid cast to TimeStampNode."; }
}

void InternalNode::createNodeList()
{
  if( node && node->data.internal_data ) {
    for( uint i = 0; i < node->data.internal_data->length; i++ ) {
      children.push_back( NodeFactory::createNode( node->data.internal_data->children[i] ) );
    }
  }
}

const Node *InternalNode::child( uint index ) const
{
  if( index <= node->data.internal_data->length )
  { return children.at(index); }
  else
  { return 0; }
}

InternalNode::~InternalNode()
{
  for( NodeIterator it = lastNode(); it != firstNode(); --it )
  {
    delete *it;
  }
}

}

