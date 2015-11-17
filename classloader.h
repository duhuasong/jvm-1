// arquivo classloader.h


/*======================================================*/
/* 	DESCRIÇÃO

- Definições das estruturas presentes no arquivo .class
- Protótipos dos métodos que carregam as informações presentes
no .class na struct ClassFile.
*/
/*======================================================*/

#ifndef	CLASSLOADER_H
#define CLASSLOADER_H

/*======================================================*/
//	INCLUDES

#include	<stdint.h>
#include	<stdio.h>
#include	"info.h"

/*======================================================*/
//	DESCRITORES DE FIELD
#define		BYTE			B
#define		CHAR			C
#define		DOUBLE			D
#define		FLOAT			F
#define		INT			I
#define		LONG			J
#define		REF_INST		L
#define		SHORT			S
#define		BOOLEAN			Z
#define		REF_ARRAY		[

/*======================================================*/
//	ACCESS FLAGS

/* Access Flags de Classe ou Interface */
#define		ACC_PUBLIC		0x0001
#define		ACC_FINAL		0x0010
#define		ACC_SUPER		0x0020
#define		ACC_INTERFACE		0x0200
#define		ACC_ABSTRACT		0x0400

/* Access Flags de Field */
#define		ACC_PUBLIC		0x0001
#define		ACC_PRIVATE		0x0002
#define		ACC_PROTECTED		0x0004
#define		ACC_STATIC		0x0008
#define		ACC_FINAL		0x0010
#define		ACC_VOLATILE		0x0040
#define		ACC_TRANSIENT		0x0080

/* Access Flags de Método */
#define		ACC_PUBLIC		0x0001
#define		ACC_PRIVATE		0x0002
#define		ACC_PROTECTED		0x0004
#define		ACC_STATIC		0x0008
#define		ACC_FINAL		0x0010
#define		ACC_SYNCHRONIZED	0x0020
#define		ACC_NATIVE		0x0100
#define		ACC_ABSTRACT		0x0400
#define		ACC_STRICT		0x0800

/* Access Flags de InnerClasses */
#define		ACC_PUBLIC		0x0001
#define		ACC_PRIVATE		0x0002
#define		ACC_PROTECTED		0x0004
#define		ACC_STATIC		0x0008
#define		ACC_FINAL		0x0010
#define		ACC_INTERFACE		0x0200
#define		ACC_ABSTRACT		0x0400

/*======================================================*/
//	TAGS (Constant Pool)
#define		CONSTANT_Class			7
#define		CONSTANT_Fieldref		9
#define		CONSTANT_Methodref		10
#define		CONSTANT_InterfaceMethodref	11
#define		CONSTANT_String			8
#define		CONSTANT_Integer		3
#define		CONSTANT_Float			4
#define		CONSTANT_Long			5
#define		CONSTANT_Double			6
#define		CONSTANT_NameAndType		12
#define		CONSTANT_Utf8			1

/*======================================================*/
//	TIPOS DE ATRIBUTOS
#define		CONSTANT_VALUE			0
#define		CODE				1
#define		DEPRECATED			2
#define		EXCEPTIONS			3
#define		INNER_CLASSES			4
#define		LINE_NUMBER_TABLE		5
#define		LOCAL_VARIABLE_TABLE		6
#define		SYNTHETIC			7
#define		SOURCE_FILE			8
#define		UNKNOWN				9

#define		ATTRIBUTE_TYPE			short

/*======================================================*/
//	TIPOS INTEGRAIS DE TAMANHO FIXO

typedef	uint8_t		u1;	// 1 byte
typedef	uint16_t	u2;	// 2 bytes
typedef	uint32_t	u4;	// 4 bytes

/*======================================================*/

// estrutura de dados ClassFile
typedef struct ClassFile{
	u4		magic;			// assinatura do arquivo .class = 0xCAFEBABE
	
	u2		minor_version;		// (m)
	u2		major_version;		// (M)	indicam a versão do arquivo no formato M.m
	
	u2		constant_pool_count;	// número de entradas da tabela constant_pool + 1
	cp_info*	constant_pool;		/* tabela de estruturas representando strings, nomes de classes,
						 interfaces, nomes de campos, etc. */
						 
	u2		access_flags;		/* máscara de bits que especifica permissões de acesso
						e propriedades da classe ou interface */
						
	u2		this_class;		/* aponta para uma estrutura CONSTANT_Class_info.
						representa a classe ou interface definida pelo classfile */
						
	u2		super_class;		/* aponta para uma estrutura CONSTANT_Class_info.
						representa a superclasse direta (classe mãe) */
						
	u2		interfaces_count;	// número de entradas no array 'interfaces'
	u2*		interfaces;		/* cada entrada desse array é um índice da constant_pool do tipo CONSTANT_Class_info,
						representa uma interface que é uma superinterface direta desta classe ou interface */
	
	u2		fields_count;		// número de entradas no array 'fields'
	field_info *	fields;			/* cada entrada desse array é uma estrutura 'field_info'
						variaveis de classe ou de instâncias declaradas nesta classe ou interface*/
	
	u2		methods_count;		// número de entradas no array 	'methods'
	method_info*	methods;		/* cada entrada desse array é uma estrutura 'method_info', contendo
						a descrição completa de um método da classe ou interface*/
						
	u2		attributes_count;	// número de entradas no array 'attributes'
	attribute_info*	attributes;		// cada entrada desse array é uma estrutura 'attribute_info'
}ClassFile;
/*======================================================*/
//	MÉTODOS

u1		u1Read(FILE *);
u2		u2Read(FILE *);
u4		u4Read(FILE *);
ATTRIBUTE_TYPE	getAttributeType(attribute_info *, ClassFile *);

ClassFile *	loadClassFile(FILE *);
ClassFile *	newClassFile();
void		setMagic(ClassFile *, FILE *);
void		setVersion(ClassFile *, FILE *);
void		setConstantPool(ClassFile *, FILE *);
void		setAccessFlags(ClassFile *, FILE *);
void		setThisClass(ClassFile *, FILE *);
void		setSuperClass(ClassFile *, FILE *);
void		setInterfaces(ClassFile *, FILE *);
void		setFields(ClassFile *, FILE *);
void		setMethods(ClassFile *, FILE *);
void		setAttributes(field_info *, method_info *, attribute_info *, ClassFile *, FILE *);
void		freeClassFile(ClassFile *);

/*======================================================*/

#endif

